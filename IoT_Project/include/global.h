#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ElegantOTA.h>
#include <DHT20.h>
#include <LiquidCrystal_I2C.h>
#include <LittleFS.h>
#include <AsyncTCP.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "lcd.h"
#include "coreiot.h"
#include "led_blinky.h"
#include "task_wifi.h"
#include "temp_humid.h"
#include "task_check_info.h"
#include "task_handler.h"
#include "task_webserver.h"

//Variables
extern float glob_temperature;
extern float glob_humidity;
extern char* COREIOT_SERVER;
extern char* COREIOT_TOKEN;
extern uint16_t MQTT_PORT;
extern char* WIFI_SSID;
extern char* WIFI_PASSWORD;

extern bool rpc_led; 

extern SemaphoreHandle_t xWifiSemaphore;

#endif