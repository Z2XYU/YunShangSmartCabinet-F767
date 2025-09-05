#pragma once

#include "main.h"

#define CONTROL_ACTION_MAX_LEN 16       // 动作字段长度
#define CONTROL_OPTION_MAX_LEN 16       // 选项字段长度

// ================== 应用层消息 ==================
typedef struct
{
    int clothes_id;
    char action[CONTROL_ACTION_MAX_LEN];
    char option[CONTROL_OPTION_MAX_LEN];
    int cabinet_location;
} MqttControl_t;


// ================== 配置宏 ==================
#define MQTT_PAYLOAD_MAX_LEN 256 // 原始 MQTT 消息缓存大小
#define MQTT_TOPIC_MAX_LEN 64    // MQTT 主题长度

// ================== 协议层消息 ==================
typedef struct
{
    char topic[MQTT_TOPIC_MAX_LEN];
    uint8_t payload[MQTT_PAYLOAD_MAX_LEN];
    uint16_t length;
    uint8_t qos;
    uint8_t retain;
} MqttMessageRaw_t;

typedef struct
{
    char client_id[32];     // 客户端 ID（唯一标识设备）
    char username[32];      // 用户名（可选）
    char password[32];      // 密码（可选）

    char server[64];        // MQTT 服务器地址（IP 或域名）
    char port[8];          // MQTT 服务器端口（一般 1883 或 8883）

    char keepalive[8];     // 保活时间（单位：秒）

    char topic[32];
    char qos[5];            // 默认 QoS 等级 (0/1/2)

    char payload[256];

} MqttConfig_t;

// ================== 消息类型 ==================
typedef enum
{
    MQTT_MSG_UNKNOWN = 0,
    MQTT_MSG_CONTROL,
} MqttMsgType_e;

// ================== 应用层通用消息 ==================
typedef struct
{
    MqttMsgType_e type;
    union
    {
        MqttControl_t control;
    } payload;
} MqttMessage_t;