#ifndef __TASK_WEBSERVER_H__
#define __TASK_WEBSERVER_H__

#include "global.h"
void Webserver_sendata(String data);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void connnectWSV();
void Webserver_stop();
void Webserver_reconnect();
void task_webserver(void *pvParameters);

#endif