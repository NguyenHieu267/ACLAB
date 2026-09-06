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
#include <esp_now.h>

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
#include "task_espnow.h" 

//Variables
extern float glob_temperature;
extern float glob_humidity;

extern String COREIOT_SERVER;
extern String COREIOT_TOKEN;
extern uint16_t MQTT_PORT;
extern String WIFI_SSID;
extern String WIFI_PASSWORD;

extern bool rpc_led; 

extern AsyncWebServer server;
extern AsyncWebSocket ws;

extern void handleWebSocketMessage(String message);

extern SemaphoreHandle_t xWifiSemaphore;
extern void startAP();

#endif