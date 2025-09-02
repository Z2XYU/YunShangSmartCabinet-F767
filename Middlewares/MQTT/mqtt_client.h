#pragma once

#include "main.h"
#include "mqtt_message.h"

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

void matt_message_handle(const MqttMessage_t *msg);