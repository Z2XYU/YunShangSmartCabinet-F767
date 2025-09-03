#pragma once

#include "main.h"
#include "cmsis_os2.h"
#include "ESP8266/esp8266.h"

typedef struct
{
    char type[32];
    char cmd[32];
    union
    {
        WifiConfig_t wifi_config;
        MqttConfig_t mqtt_config;
    } payload;
} WifiCommand_t;

typedef struct 
{
    char type[32];
    char cmd[32];
    union
    {
        WifiState_t wifi_state;
    } payload;
} WifiMessage_t;

osStatus_t wifi_send_msg_to_queue(osMessageQueueId_t queue, const WifiCommand_t *cmd, uint32_t timeout_ms);
void wifi_send_message_handle(WifiCommand_t *msg);
void wifi_recv_msg_handle(WifiMessage_t *msg);