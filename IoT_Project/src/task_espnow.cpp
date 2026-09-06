#include "global.h"

uint8_t receiverAddress[] = {0x30, 0xAE, 0xA4, 0x07, 0x0D, 0x64};       // ESP32 Receiver MAC addr
esp_now_peer_info_t peerInfo;
struct_message myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("ESP-NOW Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void task_espnow(void *pvParameters) {
    vTaskDelay(pdMS_TO_TICKS(5000)); 

    // Delete task if error
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        vTaskDelete(NULL); 
    }

    esp_now_register_send_cb(OnDataSent);

    memcpy(peerInfo.peer_addr, receiverAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
    }

    bool last_rpc_led_state = !rpc_led;

    while(1) {
        // Check if rpc_led change status
        if (rpc_led != last_rpc_led_state) {
            last_rpc_led_state = rpc_led;
            myData.led_state = rpc_led;
            
            esp_err_t result = esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));
            if (result == ESP_OK) {
                Serial.printf("Sent LED State: %d\n", myData.led_state);
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}