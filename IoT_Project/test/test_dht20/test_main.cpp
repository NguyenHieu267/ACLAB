#include <unity.h>
#include "global.h"

TaskHandle_t dhtTaskHandle = NULL;
extern float glob_temperature;
extern float glob_humidity;

void setUp() {
    glob_temperature = 0.0;
    glob_humidity = 0.0;
}

void tearDown() {
    if (dhtTaskHandle != NULL) {
        vTaskDelete(dhtTaskHandle);
        dhtTaskHandle = NULL;
    }
}

void test_dht20_reads_valid_data(void) {
    xTaskCreate(temp_humid_monitor, "DHTTest", 2048, NULL, 1, &dhtTaskHandle);
    
    // Wait 2s for task init and read data
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // 'glob_temperature' = 0.0 or <10 or > 60 => fail. 
    TEST_ASSERT_GREATER_OR_EQUAL_FLOAT(10.0, glob_temperature);
    TEST_ASSERT_LESS_OR_EQUAL_FLOAT(60.0, glob_temperature);
    
    // 'glob_humidity' <0 or >100 => fail
    TEST_ASSERT_GREATER_OR_EQUAL_FLOAT(0.0, glob_humidity);
    TEST_ASSERT_LESS_OR_EQUAL_FLOAT(100.0, glob_humidity);
}

void setup() {
    delay(2000); 

    UNITY_BEGIN(); 
    RUN_TEST(test_dht20_reads_valid_data);
    UNITY_END(); 
}
void loop() {}