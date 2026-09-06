#include "global.h"

void setup()
{
  Serial.begin(115200);

  check_info_File(0);

  xTaskCreate(led_blinky, "Task LED Blink", 2048, NULL, 2, NULL);
  xTaskCreate(lcd_task, "Task LCD Display", 2048, NULL, 2, NULL);
  xTaskCreate(temp_humid_monitor, "Task DHT20", 2048, NULL, 2, NULL);
  xTaskCreate(wifi, "Task Wifi", 8192, NULL, 2, NULL);
  xTaskCreate(coreiot_task, "Task CoreIoT", 8192, NULL, 2, NULL);
  xTaskCreate(task_webserver, "Task Webserver", 4096, NULL, 2, NULL);
  xTaskCreate(task_espnow, "Task ESPNOW", 4096, NULL, 2, NULL);
}

void loop()
{
  vTaskDelete(NULL);
}