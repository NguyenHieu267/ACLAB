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

void wifi(void *pvParameters){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     // Connect to wifi - STA mode

    while(1){
        if (WiFi.status() != WL_CONNECTED) {
            WiFi.disconnect();
            WiFi.reconnect();
            while (WiFi.status() != WL_CONNECTED) {      // Check whether wifi is connect or not
                vTaskDelay(pdMS_TO_TICKS(1000));
                Serial.print(".");                       // If NOT -> print "..........."
            }
            xSemaphoreGive(xWifiSemaphore);              // If YES -> give semaphore to setup_coreiot()
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}