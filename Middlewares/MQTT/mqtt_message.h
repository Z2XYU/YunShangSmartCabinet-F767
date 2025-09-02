#pragma once

#include "main.h"
#include "mqtt_client.h"

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

void mqtt_message_init(MqttMessage_t *msg);