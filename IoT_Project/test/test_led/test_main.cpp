#include <unity.h>
#include "global.h" 

TaskHandle_t blinkTaskHandle = NULL;
extern bool rpc_led; 


// Run before the test - set LED_GPIO to LOW 
void setUp() {                      
    pinMode(LED_GPIO, OUTPUT);
    digitalWrite(LED_GPIO, LOW);
}


// Run after the test - delete blinkTaskHandle
void tearDown() {                  
    vTaskDelete(blinkTaskHandle);
    blinkTaskHandle = NULL;
}

void test_led_blinks_when_rpc_led_is_false() {                
    rpc_led = false; 
    xTaskCreate(led_blinky, "BlinkyTest", 2048, NULL, 1, &blinkTaskHandle);
    
    // vTaskDelay(pdMS_TO_TICKS(100)); 
    // Create a script to turn the LED on for 1 second and then off.
    TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_GPIO));
    vTaskDelay(pdMS_TO_TICKS(1000)); 
    TEST_ASSERT_EQUAL(LOW, digitalRead(LED_GPIO));
}

void test_led_stays_off_when_rpc_led_is_true() {
    rpc_led = true;
    xTaskCreate(led_blinky, "BlinkyTest", 2048, NULL, 1, &blinkTaskHandle);
    
    vTaskDelay(pdMS_TO_TICKS(1000)); 
    TEST_ASSERT_EQUAL(LOW, digitalRead(LED_GPIO));
}

void setup() {
    delay(2000); 
    
    UNITY_BEGIN(); 
    RUN_TEST(test_led_blinks_when_rpc_led_is_false);
    RUN_TEST(test_led_stays_off_when_rpc_led_is_true);
    UNITY_END(); 
}
void loop() {}