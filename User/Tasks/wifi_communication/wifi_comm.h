#pragma once

#include "main.h"
#include "cmsis_os2.h"
#include "ESP8266/esp8266.h"
#include <cJSON.h>
#include "motor_control_tasks.h"
#include "clock.h"

/*类型、命令 预留枚举 wifiMsgType_e*/
typedef enum
{
    TYPE_INVALID,
    TYPE_WIFI,
    TYPE_MQTT,
    TYPE_HTTP,
    TYPE_TCP,
    TYPE_SOCKET,
    TYPE_SYSTEM,
} MsgType_t;

typedef enum
{
    WIFI_CMD_INVALID,
    WIFI_CMD_CONNECT,
    WIFI_CMD_DISCONNECT,
    WIFI_CMD_CONNECTED,
    WIFI_CMD_GET_STATUS,
    WIFI_CMD_SET_STATUS,
    WIFI_CMD_NOTICE,
    WIFI_CMD_NUM
} WifiCmd_t;

typedef enum
{
    MQTT_CMD_INVALID,
    MQTT_CMD_CONNECT,
    MQTT_CMD_SUBSCRIBE,
    MQTT_CMD_PUBLISH,
    MQTT_CMD_NUM
} MqttCmd_t;

typedef enum
{
    HTTP_CMD_INVALID,
    HTTP_CMD_GET_TIME,
    HTTP_CMD_SET_TIME,
    HTTP_CMD_NUM
} HttpCmd_t;

typedef enum
{
    TCP_CMD_INVALID,
    TCP_CMD_CONTROL,
    TCP_CMD_NUM,
} TcpCmd_t;

typedef enum
{
    SOCKET_CMD_INVALID,
    SOCKET_CMD_CONTROL,
    SOCKET_CMD_NUM,
} SocketCmd_t;

typedef enum
{
    SYS_CMD_REBOOT,
    SYS_CMD_UPDATE,
    SYS_CMD_NUM
} SystemCmd_t;

typedef struct
{
    MsgType_t type;
    union
    {
        WifiCmd_t wifi_cmd;
        MqttCmd_t mqtt_cmd;
        HttpCmd_t http_cmd;
        TcpCmd_t tcp_cmd;
        SocketCmd_t socket_cmd;
        SystemCmd_t sys_cmd;
    } cmd;
    union
    {
        WifiConfig_t wifi_config;
        MqttConfig_t mqtt_config;
    } data;
} WifiCommand_t;

typedef struct
{
    MsgType_t type;
    union
    {
        WifiCmd_t wifi_cmd;
        MqttCmd_t mqtt_cmd;
        HttpCmd_t http_cmd;
        TcpCmd_t tcp_cmd;
        SocketCmd_t socket_cmd;
        SystemCmd_t sys_cmd;
    } cmd;
    union
    {
        WifiState_t wifi_state;
        MotorControl_t control_cmd;
        Clock_t clock;
    } data;
} WifiMessage_t;

typedef void (*cmd_handler)(WifiCommand_t *msg, cJSON *root);

void copy_json_int(cJSON *data, const char *key, int *dst);
void copy_json_string(cJSON *data, const char *key, char *dst, size_t size);

void cmd_send_message_handle(WifiCommand_t *msg);
void wifi_recv_msg_handle(WifiMessage_t *msg);
void wifi_recv_msg_parse(WifiMessage_t *msg, const char *json_str);

osStatus_t wifi_recv_msg_to_queue(const WifiMessage_t *msg, uint32_t timeout_ms);
osStatus_t wifi_send_msg_to_queue(const WifiCommand_t *cmd, uint32_t timeout_ms);
