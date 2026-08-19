#include "task_wifi.h"

const char* ssid = "";
const char* password = "";

void wifi(void *pvParameters){
    WiFi.begin(ssid, password);     // Connect to wifi - STA mode

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