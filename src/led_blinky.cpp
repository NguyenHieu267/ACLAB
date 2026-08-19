#include "led_blinky.h"

void led_blinky(void *pvParameters){
  pinMode(LED_GPIO, OUTPUT);
  
  while(1) {                      
    if(!rpc_led){
      digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
      vTaskDelay(pdMS_TO_TICKS(1000));

      digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
      vTaskDelay(pdMS_TO_TICKS(1000));
    }else{
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}