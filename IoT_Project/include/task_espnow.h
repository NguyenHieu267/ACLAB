#ifndef __TASK_ESPNOW_H__
#define __TASK_ESPNOW_H__

#include "global.h"

typedef struct struct_message {
    bool led_state;
} struct_message;

void task_espnow(void *pvParameters);

#endif