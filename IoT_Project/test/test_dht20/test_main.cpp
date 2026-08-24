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
    
    // Đợi 2 giây để task khởi tạo và đọc dữ liệu vòng đầu tiên
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Kiểm tra xem dữ liệu có hợp lý không (ví dụ: nhiệt độ VN thì nằm khoảng 10-60 độ C)
    // Nếu biến glob_temperature vẫn là 0.0 hoặc bất thường thì test sẽ fail.
    TEST_ASSERT_GREATER_OR_EQUAL_FLOAT(10.0, glob_temperature);
    TEST_ASSERT_LESS_OR_EQUAL_FLOAT(60.0, glob_temperature);
    
    // Kiểm tra độ ẩm (0% - 100%)
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