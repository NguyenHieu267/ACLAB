#include <task_handler.h>

void handleWebSocketMessage(String message)
{
    Serial.println(message);
    StaticJsonDocument<256> doc;

    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
        Serial.println("JSON parse error!");
        return;
    }
    JsonObject value = doc["value"];
    if (doc["page"] == "device")
    {
        if (!value.containsKey("gpio") || !value.containsKey("status"))
        {
            Serial.println("⚠️ JSON missing gpio or status information");
            return;
        }

        int gpio = value["gpio"];
        String status = value["status"].as<String>();

        Serial.printf("⚙️ Điều khiển GPIO %d → %s\n", gpio, status.c_str());
        pinMode(gpio, OUTPUT);
        if (status.equalsIgnoreCase("ON"))
        {
            digitalWrite(gpio, HIGH);
            Serial.printf("🔆 GPIO %d ON\n", gpio);
        }
        else if (status.equalsIgnoreCase("OFF"))
        {
            digitalWrite(gpio, LOW);
            Serial.printf("💤 GPIO %d OFF\n", gpio);
        }
    }
    else if (doc["page"] == "setting")
    {
        char* WIFI_SSID = doc["value"]["ssid"];
        char* WIFI_PASS = doc["value"]["password"];
        char* CORE_IOT_TOKEN = doc["value"]["token"];
        char* CORE_IOT_SERVER = doc["value"]["server"];
        uint16_t MQTT_PORT = doc["value"]["port"];

        Serial.println("Receive config from WebSocket:");
        Serial.print("SSID: "); Serial.println(WIFI_SSID);
        Serial.print("PASS: "); Serial.println(WIFI_PASS);
        Serial.print("TOKEN: "); Serial.println(CORE_IOT_TOKEN);
        Serial.print("SERVER: "); Serial.println(CORE_IOT_SERVER);
        Serial.print("PORT: "); Serial.println(MQTT_PORT);

        Save_info_File(WIFI_SSID, WIFI_PASS, CORE_IOT_TOKEN, CORE_IOT_SERVER, MQTT_PORT);

        // Phản hồi lại client (tùy chọn)
        String msg = "{\"status\":\"ok\",\"page\":\"setting_saved\"}";
        ws.textAll(msg);
    }
}