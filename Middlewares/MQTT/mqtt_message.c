#include "mqtt_message.h"
#include <string.h>
#include "cmsis_os2.h"
#include "wifi_comm.h"
#include "wifi_tasks.h"

static MqttConfig_t mqtt;
/* 初始化应用层 MQTT 消息结构体 */
void mqtt_init(char *id, char *username, char *password, char *server, char* port, char* keepalive)
{
    strcpy(mqtt.client_id, id);
    strcpy(mqtt.username, username);
    strcpy(mqtt.password, password);

    strcpy(mqtt.server, server);
    strncpy(mqtt.port, port,sizeof(mqtt.port)-1);
    strncpy(mqtt.keepalive,keepalive,sizeof(mqtt.keepalive)-1);
}

void mqtt_connect(void)
{
    WifiCommand_t msg = {0};

    strncpy(msg.type, "mqtt", sizeof(msg.type) - 1);
    strncpy(msg.cmd, "mqtt_connect", sizeof(msg.cmd) - 1);
    strncpy(msg.data.mqtt_config.client_id, mqtt.client_id, sizeof(msg.data.mqtt_config.client_id) - 1);
    strncpy(msg.data.mqtt_config.username, mqtt.username, sizeof(msg.data.mqtt_config.username) - 1);
    strncpy(msg.data.mqtt_config.password, mqtt.password, sizeof(msg.data.mqtt_config.password) - 1);
    strncpy(msg.data.mqtt_config.server, mqtt.server, sizeof(msg.data.mqtt_config.server) - 1);

    strncpy(msg.data.mqtt_config.port, mqtt.port, sizeof(msg.data.mqtt_config.port) - 1);
    strncpy(msg.data.mqtt_config.keepalive, mqtt.keepalive, sizeof(msg.data.mqtt_config.keepalive) - 1);
    wifi_send_msg_to_queue(&msg, 0);
}

void mqtt_subscribe_tpoic(const char *topic, const char *qos)
{
    WifiCommand_t msg = {0};

    strncpy(msg.type, "mqtt", sizeof(msg.type) - 1);
    strncpy(msg.cmd, "subscribe", sizeof(msg.cmd) - 1);
    strncpy(msg.data.mqtt_config.topic, topic, sizeof(msg.data.mqtt_config.topic) - 1);
    strncpy(msg.data.mqtt_config.qos,qos,sizeof(msg.data.mqtt_config.qos)-1);

    wifi_send_msg_to_queue(&msg, 0);
}

void mqtt_publish(const char *topic, char *payload)
{
    WifiCommand_t msg = {0};

    strncpy(msg.type, "mqtt", sizeof(msg.type) - 1);
    strncpy(msg.cmd, "publish", sizeof(msg.cmd) - 1);

    strncpy(msg.data.mqtt_config.topic, topic, sizeof(msg.data.mqtt_config.topic) - 1);
    strncpy(msg.data.mqtt_config.payload, payload, sizeof(msg.data.mqtt_config.payload) - 1);

    wifi_send_msg_to_queue(&msg, 0);
}