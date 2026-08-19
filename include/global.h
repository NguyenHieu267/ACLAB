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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "lcd.h"
#include "coreiot.h"
#include "led_blinky.h"
#include "task_wifi.h"
#include "temp_humid.h"

//Variables
extern float glob_temperature;
extern float glob_humidity;
extern const char* coreIOT_Server;
extern const char* coreIOT_Token;
extern const int mqttPort;

extern bool rpc_led; 

extern SemaphoreHandle_t xWifiSemaphore;

#endif