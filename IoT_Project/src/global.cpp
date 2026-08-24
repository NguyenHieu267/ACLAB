#include "global.h"

float glob_temperature = 0;
float glob_humidity = 0;

bool rpc_led = false;

String COREIOT_SERVER = "";
String COREIOT_TOKEN = "";
uint16_t MQTT_PORT = 0;

String WIFI_SSID = "";
String WIFI_PASSWORD = "";

SemaphoreHandle_t xWifiSemaphore = xSemaphoreCreateBinary();
