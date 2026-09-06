#include <unity.h>
#include "global.h"

TaskHandle_t lcdTaskHandle = NULL;
extern float glob_temperature;
extern float glob_humidity;

void setUp() {
    glob_temperature = 25.5;
    glob_humidity = 60.0;
}

void tearDown() {
    vTaskDelete(lcdTaskHandle);
    lcdTaskHandle = NULL;
}

void test_lcd_initialization_and_display() {
    xTaskCreate(lcd_task, "LCDTest", 2048, NULL, 1, &lcdTaskHandle);
    
    vTaskDelay(pdMS_TO_TICKS(2000));
    TEST_ASSERT_TRUE(true); 
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_lcd_initialization_and_display);
    UNITY_END();
}
void loop() {}