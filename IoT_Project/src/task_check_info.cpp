#include "task_check_info.h"

void Load_info_File() {
  File file = LittleFS.open("/info.dat", "r");  // Open /info.data to read("r")
  if (!file) return;

  DynamicJsonDocument doc(4096);
  DeserializationError error = deserializeJson(doc, file); //Parses a JSON input (file), filters, and puts the result in a JsonDocument (doc).
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
  } else { // Load data to global variables
    WIFI_SSID       = strdup(doc["WIFI_SSID"]);                  
    WIFI_PASSWORD   = strdup(doc["WIFI_PASS"]);
    COREIOT_TOKEN   = strdup(doc["CORE_IOT_TOKEN"]);
    COREIOT_SERVER  = strdup(doc["CORE_IOT_SERVER"]);
    MQTT_PORT       = doc["CORE_IOT_PORT"];
  }
    file.close();
}

void Delete_info_File() {
  if (LittleFS.exists("/info.dat"))
  {
    LittleFS.remove("/info.dat");
  }
  ESP.restart();
}

void Save_info_File(String wifi_ssid, String wifi_pass, String coreiot_token, String coreiot_server, uint16_t mqtt_port)
{
  Serial.println(wifi_ssid);
  Serial.println(wifi_pass);

  DynamicJsonDocument doc(4096);
  doc["WIFI_SSID"] = wifi_ssid;
  doc["WIFI_PASS"] = wifi_pass;
  doc["CORE_IOT_TOKEN"] = coreiot_token;
  doc["CORE_IOT_SERVER"] = coreiot_server;
  doc["CORE_IOT_PORT"] = mqtt_port;

  File configFile = LittleFS.open("/info.dat", "w");      // Open /info.data to write("w")
  if (configFile)
  {
    serializeJson(doc, configFile);
    configFile.close();
  }
  else
  {
    Serial.println("Unable to save the configuration."); 
  }
  ESP.restart();
};

bool check_info_File(bool check)
{
  if (!check)           // check == false (1st initialize)
  {
    if (!LittleFS.begin(true))
    {
      Serial.println("LittleFS initialization error!");
      return false;
    }
    Load_info_File();
  }

  if (WIFI_SSID.isEmpty() && WIFI_PASSWORD.isEmpty()) {
    if (!check) {       // If 1st initialize
      startAP();        // Start AP mode
    }
    return false;       
  }
  
  return true; 
}