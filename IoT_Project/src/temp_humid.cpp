#include "temp_humid.h"
#include "AIoT_Project_inferencing.h"

DHT20 dht20;
float sensor_buffer[10];
int sample_index = 0;
uint32_t current_delay = 1000; 

void temp_humid_monitor(void *parameters){
    dht20.begin();

    while(1){
        dht20.read();
        float temperature = dht20.getTemperature();
        float humidity    = dht20.getHumidity();
        
        glob_temperature = temperature;
        glob_humidity = humidity;

        sensor_buffer[sample_index++] = temperature;
        sensor_buffer[sample_index++] = humidity;

        if (sample_index >= 10) {
            signal_t signal;
            int err = numpy::signal_from_buffer(sensor_buffer, 10, &signal);
            
            if (err == 0) {
                ei_impulse_result_t result = { 0 };
                EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

                if (res == EI_IMPULSE_OK) {
                    Serial.printf("AI phan doan - Stable: %.2f | Volatile: %.2f\n", 
                                  result.classification[0].value, 
                                  result.classification[1].value);
                    
                    if (result.classification[1].value > 0.6) {
                        current_delay = 1000;  
                        Serial.println("-> Trang thai: BIEN DONG. Chuyen chu ky doc thanh 1s.");
                    } else {
                        current_delay = 10000; 
                        Serial.println("-> Trang thai: ON DINH. Chuyen chu ky doc thanh 10s.");
                    }
                } else {
                    Serial.printf("Loi khi chay AI: %d\n", res);
                }
            }
            
            sample_index = 0; 
        }
        vTaskDelay(pdMS_TO_TICKS(current_delay));
    }
}