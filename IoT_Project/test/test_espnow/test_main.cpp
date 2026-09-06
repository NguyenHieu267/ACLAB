#include <Arduino.h>
#include <unity.h>
#include <WiFi.h>
#include <esp_now.h>

void setUp(void) {
    WiFi.mode(WIFI_STA);
}

void tearDown(void) {
    esp_now_deinit();
}

// Test: Check ESP-NOW init 
void test_esp_now_init_success(void) {
    esp_err_t result = esp_now_init();
    TEST_ASSERT_EQUAL_MESSAGE(ESP_OK, result, "ESP-NOW Init Failed!");
}

// Test: Check Add ESP-NOW peer 
void test_add_peer(void) {
    esp_now_init(); 
    
    esp_now_peer_info_t peerInfo;
    uint8_t dummyAddress[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};          // Random MAC addr
    memcpy(peerInfo.peer_addr, dummyAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    esp_err_t result = esp_now_add_peer(&peerInfo);
    TEST_ASSERT_EQUAL_MESSAGE(ESP_OK, result, "Cannot add ESP-NOW Peer");
}

void setup() {
    delay(2000); 
    
    UNITY_BEGIN();
    RUN_TEST(test_esp_now_init_success);
    RUN_TEST(test_add_peer);
    UNITY_END();
}

void loop() {
   
}