#include "global.h"

float glob_temperature = 0;
float glob_humidity = 0;

bool rpc_led = false;

char* COREIOT_SERVER = "";
char* COREIOT_TOKEN = "";
uint16_t MQTT_PORT = 0;

char* WIFI_SSID = "";
char* WIFI_PASSWORD = "";

SemaphoreHandle_t xWifiSemaphore = xSemaphoreCreateBinary();
