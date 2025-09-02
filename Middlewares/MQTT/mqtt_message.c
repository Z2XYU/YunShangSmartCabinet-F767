#include "mqtt_message.h"
#include <string.h>

/* 初始化应用层 MQTT 消息结构体 */
void mqtt_message_init(MqttMessage_t *msg)
{
    if (!msg)
        return;

    // 初始化类型
    msg->type = MQTT_MSG_UNKNOWN;

    // 清空联合体 payload
    memset(&msg->payload, 0, sizeof(msg->payload));
}