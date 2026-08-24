#include "coreiot.h"

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()){           // If cannot to Core IoT
    String clientId = "ESP32Client-";            // Initialize Client name for ESP32 to connect to MQTT (Core IoT)
    clientId += String(random(0xffff), HEX);     // Ex: ESP32Client-A1B2 

    if(client.connect(clientId.c_str(), COREIOT_TOKEN.c_str(), NULL)){        // connect(const char *id, const char *user, const char *pass)    -> .c_str()
      client.subscribe("v1/devices/me/rpc/request/+");      // topic to "Subscribe to server-side RPC"
    }else{
      Serial.print("failed, rc=");
      Serial.print(client.state());               // Error Code to debug
      Serial.println(" try again in 5 seconds");
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length){  
  char message[length + 1];             // params "ON" - length=16 (8x2) => length + 1 = 17 (ON\0)
  memcpy(message, payload, length);     // memcpy(to, from, num); - copy data *from --> *to  
  message[length] = '\0';
  Serial.print("Payload: ");
  Serial.println(message);

  // Parse JSON
  StaticJsonDocument<256> doc;  // Initialize stack 'doc' 256 bytes to store JSON
  DeserializationError error = deserializeJson(doc, message);    // read JSON from message to doc

  if(error){
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* method = doc["method"];  // Find "method" in 'doc'
  if (strcmp(method, "setStateLED") == 0) {   // Compare string in method and "setStateLED"
    const char* params = doc["params"];     // Example: {"method": "setValueLED", "params": "ON"}

    if(strcmp(params, "ON") == 0){
      Serial.println("Device turned ON.");
      rpc_led = true;
      digitalWrite(LED_GPIO, HIGH);
    }else{   
      Serial.println("Device turned OFF.");
      rpc_led = true;
      digitalWrite(LED_GPIO, LOW);

    }
  } else {
    Serial.print("Unknown method: ");
    Serial.println(method);
  }
}


void setup_coreiot(){
  while(1){
    if(xSemaphoreTake(xWifiSemaphore, portMAX_DELAY)){
      break;
    }
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.print(".");
  }

  Serial.println(" Connected!");

  client.setServer(COREIOT_SERVER.c_str(), MQTT_PORT);
  client.setCallback(callback);
}


void coreiot_task(void *pvParameters){
    setup_coreiot();

    while(1){
        if (!client.connected()){
            reconnect();
        }
        client.loop();

        // Sample payload, publish to 'v1/devices/me/telemetry'
        String payload = "{\"temperature\":" + String(glob_temperature) +  ",\"humidity\":" + String(glob_humidity) + "}";
        client.publish("v1/devices/me/telemetry", payload.c_str());

        Serial.println("Published payload: " + payload);
        vTaskDelay(5000);  // Publish every 5 seconds
    }
}