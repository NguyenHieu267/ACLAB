#include "task_webserver.h"

AsyncWebServer server(80);          // HTTP port
AsyncWebSocket ws("/ws");           // WebSocket

bool webserver_isrunning = false;

void Webserver_sendata(String data)
{
    if (ws.count() > 0)
    {
        ws.textAll(data); // Send to all client connecting
        Serial.println("Data sent via WebSocket:" + data);
    }
    else
    {
        Serial.println("No WebSocket client is currently connected!");
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type) {
        case WS_EVT_CONNECT:        // Client open web
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break; 

        case WS_EVT_DISCONNECT:     // Client close web
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;

        case WS_EVT_DATA:{           // Client press button on web
            AwsFrameInfo *info = (AwsFrameInfo *)arg;
            if (info->opcode == WS_TEXT)
            {
                String message;
                message += String((char *)data).substring(0, len);
                handleWebSocketMessage(message); // parseJson(message, true);
            }
            }break; 

        default:break;
    }
}

void connnectWSV()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", "text/html"); }); // When user access home page ("/") -> LittleFS and retrieve ("index.html") and send it
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/script.js", "application/javascript"); });
    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/styles.css", "text/css"); });
              
    ElegantOTA.begin(&server); 
    server.begin();
    webserver_isrunning = true;
}

void Webserver_stop()
{
    ws.closeAll();
    server.end();
    webserver_isrunning = false;
}

void Webserver_reconnect()
{
    if (!webserver_isrunning)
    {
        connnectWSV();
    }
}

void task_webserver(void *pvParameters)
{
    while(1){
        if( WiFi.getMode() == WIFI_AP || 
           (WiFi.getMode() == WIFI_STA && WiFi.status() == WL_CONNECTED) ){
            Webserver_reconnect();
            
            // Check to update firmware OTA
            if (webserver_isrunning) ElegantOTA.loop();

        }else{
            Webserver_stop();
        }
        vTaskDelay(20);
    }
}