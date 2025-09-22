#include "websocket_handler.h"
#include <stdio.h>

static void motor_control_parse(WifiMessage_t *msg, cJSON *data)
{
    if (!msg || !data)
        return;

    // 拷贝整数字段
    copy_json_int(data, "clothes_id", &msg->data.control_cmd.clothes_id);
    copy_json_int(data, "cabinet_location", &msg->data.control_cmd.cabinet_location);

    // 拷贝字符串字段
    copy_json_string(data, "action", msg->data.control_cmd.action, sizeof(msg->data.control_cmd.action));
    copy_json_string(data, "option", msg->data.control_cmd.option, sizeof(msg->data.control_cmd.option));
}

void socket_msg_parse(WifiMessage_t *msg, const char *json_str)
{
    if (!msg || !json_str)
        return;

    cJSON *root = cJSON_Parse(json_str);
    if (!root)
        return;

    cJSON *data = cJSON_GetObjectItem(root, "data");
    if (!data)
    {
        cJSON_Delete(root);
        return;
    }

    switch (msg->cmd.socket_cmd)
    {
    case SOCKET_CMD_CONTROL:
        motor_control_parse(msg, data);
        break;

    default:
        break;
    }
}

static void motor_control_cmd(WifiMessage_t *msg)
{
    osMessageQueuePut(motorControlMsgQueueHandle, msg, 0, 0);
}

void socket_recv_msg(WifiMessage_t *msg)
{
    if (!msg)
        return;

    switch (msg->cmd.socket_cmd)
    {
    case SOCKET_CMD_CONTROL:
        motor_control_cmd(msg);
        break;

    default:
        break;
    }
}