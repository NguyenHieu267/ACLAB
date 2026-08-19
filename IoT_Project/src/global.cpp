#include "global.h"

float glob_temperature = 0;
float glob_humidity = 0;

bool rpc_led = false;

const char* coreIOT_Server = "app.coreiot.io";  
const char* coreIOT_Token  = "b01WKid1t1mKpr38KeFr";    // ESP_Node_01 
const int   mqttPort       = 1883;

SemaphoreHandle_t xWifiSemaphore = xSemaphoreCreateBinary();
