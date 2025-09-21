#include "mqtt_handler.h"

void mqtt_connect_pack(WifiCommand_t *msg, cJSON *root)
{
    cJSON *data = cJSON_CreateObject();
    if (data)
    {
        cJSON_AddStringToObject(data, "client_id", msg->data.mqtt_config.client_id);
        cJSON_AddStringToObject(data, "username", msg->data.mqtt_config.username);
        cJSON_AddStringToObject(data, "password", msg->data.mqtt_config.password);
        cJSON_AddStringToObject(data, "server", msg->data.mqtt_config.server);
        cJSON_AddStringToObject(data, "port", msg->data.mqtt_config.port);
        cJSON_AddStringToObject(data, "keepalive", msg->data.mqtt_config.keepalive);
        cJSON_AddItemToObject(root, "data", data);
    }
}

void mqtt_subscribe_pcak(WifiCommand_t *msg, cJSON *root)
{
    cJSON *data = cJSON_CreateObject();
    if (data)
    {
        cJSON_AddStringToObject(data, "topic", msg->data.mqtt_config.topic);
        cJSON_AddStringToObject(data, "qos", msg->data.mqtt_config.qos);
        cJSON_AddItemToObject(root, "data", data);
    }
}
void mqtt_publish_pack(WifiCommand_t *msg, cJSON *root)
{
    cJSON *data = cJSON_CreateObject();
    cJSON_AddStringToObject(data, "topic", msg->data.mqtt_config.topic);
    cJSON_AddStringToObject(data, "payload", msg->data.mqtt_config.payload);
    cJSON_AddItemToObject(root, "data", data);
}

void mqtt_recv_msg(WifiMessage_t *msg)
{
}