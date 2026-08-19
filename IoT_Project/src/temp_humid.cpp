#include "temp_humid.h"

DHT20 dht20;

void temp_humid_monitor(void *parameters){
    dht20.begin();

    while(1){
        dht20.read();

        float temperature = dht20.getTemperature();
        float humidity    = dht20.getHumidity();
        
        glob_temperature = temperature;
        glob_humidity = humidity;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
