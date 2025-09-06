#pragma once

#include "main.h"
#include "cmsis_os2.h"
#include "ESP8266/esp8266.h"
#include <cJSON.h>
#include "motor_control_task.h"

typedef struct
{
    char type[32];
    char cmd[32];
    union
    {
        WifiConfig_t wifi_config;
        MqttConfig_t mqtt_config;
    } data;
} WifiCommand_t;

typedef struct
{
    char type[32];
    char cmd[32];
    union
    {
        WifiState_t wifi_state;
        char notice[64];
        MotorControl_t control_cmd;
    } data;
} WifiMessage_t;

typedef void (*wifi_cmd_handler)(WifiMessage_t *msg, cJSON *data);
typedef void (*mqtt_cmd_handler)(WifiMessage_t *msg, cJSON *data);

typedef struct
{
    const char *cmd;          // 命令字符串
    wifi_cmd_handler handler; // 处理函数
} WifiCmdMap_t;

typedef struct
{
    const char *cmd;          // 命令字符串
    mqtt_cmd_handler handler; // 处理函数
} MqttCmdMap_t;

void wifi_send_message_handle(WifiCommand_t *msg);
void wifi_recv_msg_handle(WifiMessage_t *msg);
void wifi_recv_msg_parse(WifiMessage_t *msg, const char *json_str);

osStatus_t wifi_recv_msg_to_queue( const WifiMessage_t *msg, uint32_t timeout_ms);
osStatus_t wifi_send_msg_to_queue( const WifiCommand_t *cmd, uint32_t timeout_ms);
