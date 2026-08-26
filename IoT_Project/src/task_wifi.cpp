#include "task_wifi.h"

void startAP()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(String(SSID_AP), String(PASS_AP));
    Serial.println("📡 AP Mode Started!");
    Serial.print("SSID: ");
    Serial.println(String(SSID_AP));
    Serial.print("Password: ");
    Serial.println(String(PASS_AP));
    Serial.print("🌐 AP IP: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("✅ Connect to this WiFi and open: http://192.168.4.1");
}

void startSTA()
{
    if (WIFI_SSID.isEmpty()) return;

    WiFi.mode(WIFI_STA);

    if (WIFI_PASSWORD.isEmpty()){
        WiFi.begin(WIFI_SSID.c_str());
    }else{
        WiFi.begin(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str());
    }

    while(WiFi.status() != WL_CONNECTED){
        vTaskDelay(pdMS_TO_TICKS(1000));
        Serial.print(".");  
    }
    
    xSemaphoreGive(xWifiSemaphore);
}

void wifi(void *pvParameters)
{
    if (WIFI_SSID.isEmpty()) vTaskDelete(NULL);
    startSTA();
    Serial.println("✅ Connect again to WiFi:" + WIFI_SSID);
    Serial.print("and open: http://" + WiFi.localIP().toString());

    while (1){
        if (WiFi.status() != WL_CONNECTED) 
        {
            WiFi.disconnect();
            WiFi.reconnect();
            while (WiFi.status() != WL_CONNECTED) 
            {
                vTaskDelay(pdMS_TO_TICKS(1000));
                Serial.print("."); 
            }
            Serial.println("✅ Connect again to WiFi:" + WIFI_SSID);
            Serial.print("and open: http://" + WiFi.localIP().toString());
            xSemaphoreGive(xWifiSemaphore); 
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}