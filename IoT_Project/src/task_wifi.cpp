#include "task_wifi.h"

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