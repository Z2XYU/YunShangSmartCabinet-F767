#include "wifi_comm.h"
#include "wifi_tasks.h"
#include "usart.h"
#include "string.h"
#include "cJSON.h"
#include <stdio.h>
#include "mqtt_message.h"
#include "motor_control_tasks.h"
#include "clock.h"
#include "gui_guider.h"
#include "custom.h"
#include "ui_tasks.h"

#include "wifi_handler/wifi_handler.h"
#include "mqtt_handler/mqtt_handler.h"
#include "http_handler/http_handler.h"
#include "tcp_handler/tcp_handler.h"
#include "websocket_handler/websocket_handler.h"

// 向消息队列发送消息
osStatus_t wifi_send_msg_to_queue(const WifiCommand_t *cmd, uint32_t timeout_ms)
{
    return osMessageQueuePut(
        wifiSendQueueHandle,
        cmd,
        0,
        timeout_ms);
}

osStatus_t wifi_recv_msg_to_queue(const WifiMessage_t *msg, uint32_t timeout_ms)
{
    return osMessageQueuePut(
        wifiRecvQueueHandle, // 使用传入的队列
        msg,
        0,         // 优先级
        timeout_ms // 超时
    );
}

void copy_json_int(cJSON *data, const char *key, int *dst)
{
    if (!data || !dst)
        return;

    cJSON *item = cJSON_GetObjectItem(data, key);
    if (cJSON_IsNumber(item))
    {
        *dst = item->valueint;
    }
}

void copy_json_string(cJSON *data, const char *key, char *dst, size_t size)
{
    if (!data || !dst || size == 0)
        return;

    cJSON *item = cJSON_GetObjectItem(data, key);
    if (cJSON_IsString(item) && item->valuestring)
    {
        // 使用 snprintf 避免截断溢出
        snprintf(dst, size, "%s", item->valuestring);
    }
}

static char uart_buf[512];

static void msg_send(const char *json_str)
{
    if (json_str == NULL)
        return;

    size_t len = strlen(json_str);
    if (len == 0 || len > sizeof(uart_buf) - 2)
        return;

    strcpy(uart_buf, json_str);
    uart_buf[len] = '\n'; // 添加换行
    uart_buf[len + 1] = '\0';

    printf("tx:%s", uart_buf);

    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)uart_buf, (uint16_t)(len + 1));
}

static const cmd_handler wifi_cmd_table[WIFI_CMD_NUM] = {
    [WIFI_CMD_CONNECT] = wifi_connect_pack,
    [WIFI_CMD_DISCONNECT] = wifi_disconnect_pack,
    [WIFI_CMD_GET_STATUS] = wifi_get_status_pack,
};

static const cmd_handler http_cmd_table[HTTP_CMD_NUM] = {
    [HTTP_CMD_GET_TIME] = get_beijing_time_pack,
};

static const cmd_handler mqtt_cmd_table[MQTT_CMD_NUM] = {
    [MQTT_CMD_CONNECT] = mqtt_connect_pack,
    [MQTT_CMD_SUBSCRIBE] = mqtt_subscribe_pcak,
    [MQTT_CMD_PUBLISH] = mqtt_publish_pack,
};

void cmd_send_message_handle(WifiCommand_t *msg)
{
    if (!msg)
        return;

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return;

    cJSON_AddNumberToObject(root, "type", msg->type);

    switch (msg->type)
    {
    case TYPE_WIFI:
        cJSON_AddNumberToObject(root, "cmd", msg->cmd.wifi_cmd);
        if (wifi_cmd_table[msg->cmd.wifi_cmd] && (int)msg->cmd.wifi_cmd < WIFI_CMD_NUM)
            wifi_cmd_table[msg->cmd.wifi_cmd](msg, root);
        break;

    case TYPE_MQTT:
        cJSON_AddNumberToObject(root, "cmd", msg->cmd.mqtt_cmd);
        if (mqtt_cmd_table[msg->cmd.mqtt_cmd] && (int)msg->cmd.wifi_cmd < MQTT_CMD_NUM)
            mqtt_cmd_table[msg->cmd.mqtt_cmd](msg, root);
        break;

    case TYPE_HTTP:
        cJSON_AddNumberToObject(root, "cmd", msg->cmd.http_cmd);
        if (http_cmd_table[msg->cmd.http_cmd] && (int)msg->cmd.wifi_cmd < HTTP_CMD_NUM)
            http_cmd_table[msg->cmd.http_cmd](msg, root);
        break;

    default:
        break;
    }

    char *out = cJSON_PrintUnformatted(root);
    if (out)
    {
        msg_send(out);
        cJSON_free(out);
    }

    cJSON_Delete(root);
}

void wifi_recv_msg_parse(WifiMessage_t *msg, const char *json_str)
{
    if (msg == NULL || json_str == NULL)
        return;

    cJSON *root = cJSON_Parse(json_str);

    if (root == NULL)
        return;

    cJSON *type_item = cJSON_GetObjectItem(root, "type");
    cJSON *cmd_item = cJSON_GetObjectItem(root, "cmd");

    if (!type_item || !cmd_item)
    {
        cJSON_Delete(root);
        return;
    }
    // 解析type
    msg->type = (MsgType_t)cJSON_GetNumberValue(type_item);
    switch (msg->type)
    {
    case TYPE_WIFI:
        msg->cmd.wifi_cmd = (WifiCmd_t)cJSON_GetNumberValue(cmd_item);
        wifi_msg_parse(msg, json_str);
        break;

    case TYPE_MQTT:
        msg->cmd.mqtt_cmd = (MqttCmd_t)cJSON_GetNumberValue(cmd_item);
        break;

    case TYPE_HTTP:
        msg->cmd.http_cmd = (HttpCmd_t)cJSON_GetNumberValue(cmd_item);
        http_msg_parse(msg, json_str);

    case TYPE_TCP:
        msg->cmd.tcp_cmd = (TcpCmd_t)cJSON_GetNumberValue(cmd_item);
        tcp_msg_parse(msg, json_str);

    case TYPE_SOCKET:
        msg->cmd.socket_cmd = (SocketCmd_t)cJSON_GetNumberValue(cmd_item);
        socket_msg_parse(msg, json_str);
    default:
        break;
    }

    cJSON_Delete(root);
}

void wifi_recv_msg_handle(WifiMessage_t *msg)
{
    if (msg == NULL)
        return;

    switch (msg->type)
    {
    case TYPE_WIFI:
        wifi_recv_msg(msg);
        break;
    case TYPE_MQTT:
        mqtt_recv_msg(msg);
        break;
    case TYPE_HTTP:
        http_recv_msg(msg);
        break;

    case TYPE_TCP:
        tcp_recv_msg(msg);

    case TYPE_SOCKET:
        socket_recv_msg(msg);
    default:
        break;
    }
}