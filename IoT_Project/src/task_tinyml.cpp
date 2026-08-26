#include "tinyml.h"

void task_tinyml(void *pvParameters)
{
    Serial.println("🧠 TinyML Task bắt đầu khởi động...");
    
    float temp_features[10] = {0};
    int index = 0;

    vTaskDelay(pdMS_TO_TICKS(2000)); 

    while (1)
    {
        temp_features[index] = glob_temperature;
        index = (index + 1) % 10; // Xoay vòng mảng (0-9)

        signal_t features_signal;
        int err = numpy::signal_from_buffer(temp_features, 10, &features_signal);
        
        ei_impulse_result_t result = { 0 };
        err = run_classifier(&features_signal, &result, false);

        if (result.classification[1].value > 0.8) { 
            Serial.println("🔥 AI PHÁT HIỆN NHIỆT ĐỘ TĂNG BẤT THƯỜNG!");
        }
        
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}