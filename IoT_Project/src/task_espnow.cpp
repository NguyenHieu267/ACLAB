#include "espnow.h"

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    Serial.print("📨 ESP-NOW Nhận: ");
    for(int i = 0; i < len; i++) {
        Serial.print((char)incomingData[i]);
    }
    Serial.println();
}

void task_espnow(void *pvParameters)
{
    while (WiFi.status() != WL_CONNECTED && WiFi.getMode() != WIFI_AP) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    Serial.println("⚡ Khởi tạo ESP-NOW...");
    if (esp_now_init() != ESP_OK) {
        Serial.println("❌ Lỗi khởi tạo ESP-NOW, tự hủy task!");
        vTaskDelete(NULL);
    }

    esp_now_register_recv_cb(OnDataRecv);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0; 
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("❌ Lỗi thêm Peer ESP-NOW");
    }

    while (1)
    {
        String msg = "T:" + String(glob_temperature);
        esp_now_send(broadcastAddress, (uint8_t *)msg.c_str(), msg.length());
        
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}