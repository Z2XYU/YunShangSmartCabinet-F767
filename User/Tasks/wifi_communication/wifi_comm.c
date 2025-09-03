#include "wifi_comm.h"
#include "wifi_tasks.h"
#include "usart.h"
#include "string.h"
#include "cJSON.h"

static char uart_buf[512];

// 前向声明
static void status_handle(WifiMessage_t *msg, cJSON *data);

#define WIFI_CMD_TABLE_SIZE 1
WifiCmdMap_t wifi_cmd_table[] = {
    {"status", status_handle},
    // 以后新增命令直接在这里加
};

// 向消息队列发送消息
osStatus_t wifi_send_msg_to_queue(const WifiCommand_t *cmd, uint32_t timeout_ms)
{
    return osMessageQueuePut(
        wifiSendQueueHandle, // 使用传入的队列
        cmd,
        0,         // 优先级
        timeout_ms // 超时
    );
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

static void msg_send(const char *json_str)
{
    if (json_str == NULL)
        return;

    size_t len = strlen(json_str);
    if (len == 0 || len > sizeof(uart_buf) - 2)
        return;

    // 等待上一条 DMA 发送完成
    while (HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY)
        osDelay(1);

    strcpy(uart_buf, json_str);
    uart_buf[len] = '\n'; // 添加换行
    uart_buf[len + 1] = '\0';

    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)uart_buf, (uint16_t)(len + 1));
}

void wifi_send_message_handle(WifiCommand_t *msg)
{
    cJSON *root = cJSON_CreateObject();
    char *out = NULL;
    cJSON_AddStringToObject(root, "type", msg->type);
    cJSON_AddStringToObject(root, "cmd", msg->cmd);
    if (strcmp(msg->type, "wifi") == 0)
    {
        if (strcmp(msg->cmd, "wifi_get_status") == 0)
        {
            out = cJSON_PrintUnformatted(root);
        }
        else if (strcmp(msg->cmd, "wifi_connect") == 0)
        {
            cJSON_AddStringToObject(root, "ssid", msg->data.wifi_config.ssid);
            cJSON_AddStringToObject(root, "password", msg->data.wifi_config.password);
            out = cJSON_PrintUnformatted(root);
        }
        msg_send(out);
        cJSON_free(out);
    }
    cJSON_Delete(root);
}

void wifi_recv_msg_handle(WifiMessage_t *msg)
{
    if (msg == NULL)
        return;

    if (strcmp(msg->type, "wifi") == 0)
    {
        if (strcmp(msg->cmd, "wifi_status_update") == 0)
        {
            osMutexAcquire(wifiStateMutex, osWaitForever);
            wifi_set_status(&msg->data.wifi_state);
            osMutexRelease(wifiStateMutex);
        }
    }
}

void wifi_recv_msg_parse(WifiMessage_t *msg, const char *json_str)
{
    if (msg == NULL || json_str == NULL)
        return;

    cJSON *root = cJSON_Parse(json_str);

    if (root == NULL)
        return;

    // 解析type
    cJSON *type_item = cJSON_GetObjectItem(root, "type");
    if (cJSON_IsString(type_item) && type_item->valuestring != NULL)
    {
        strncpy(msg->type, type_item->valuestring, sizeof(msg->type) - 1);
        msg->type[sizeof(msg->type) - 1] = '\0';
    }

    if (strcmp(msg->type, "wifi") == 0)
    {
        cJSON *cmd_item = cJSON_GetObjectItem(root, "cmd");
        if (cJSON_IsString(cmd_item) && cmd_item->valuestring != NULL)
        {
            strncpy(msg->cmd, cmd_item->valuestring, sizeof(msg->cmd) - 1);
            msg->cmd[sizeof(msg->cmd) - 1] = '\0';
        }
        for (size_t i = 0; i < WIFI_CMD_TABLE_SIZE; i++)
        {
            if (strcmp(msg->cmd, wifi_cmd_table[i].cmd) == 0)
            {
                if (wifi_cmd_table[i].handler != NULL)
                {
                    cJSON *data_item = cJSON_GetObjectItem(root, "data");
                    wifi_cmd_table[i].handler(msg, data_item);
                }
                break;
            }
        }
    }
    cJSON_Delete(root);
}

static void status_handle(WifiMessage_t *msg, cJSON *data)
{
    if (!msg || !data)
        return;

    cJSON *item = NULL;

    // status
    item = cJSON_GetObjectItem(data, "status");
    if (cJSON_IsNumber(item))
        msg->data.wifi_state.status = (WifiStatus_e)item->valueint;

    // ssid
    item = cJSON_GetObjectItem(data, "ssid");
    if (cJSON_IsString(item) && item->valuestring)
    {
        strncpy(msg->data.wifi_state.ssid, item->valuestring, sizeof(msg->data.wifi_state.ssid) - 1);
        msg->data.wifi_state.ssid[sizeof(msg->data.wifi_state.ssid) - 1] = '\0';
    }

    // bssid
    item = cJSON_GetObjectItem(data, "bssid");
    if (cJSON_IsString(item) && item->valuestring)
    {
        strncpy(msg->data.wifi_state.bssid, item->valuestring, sizeof(msg->data.wifi_state.bssid) - 1);
        msg->data.wifi_state.bssid[sizeof(msg->data.wifi_state.bssid) - 1] = '\0';
    }

    // rssi
    item = cJSON_GetObjectItem(data, "rssi");
    if (cJSON_IsNumber(item))
        msg->data.wifi_state.signal_strength = item->valueint;

    // local_ip
    item = cJSON_GetObjectItem(data, "local_ip");
    if (cJSON_IsString(item) && item->valuestring)
    {
        strncpy(msg->data.wifi_state.ip, item->valuestring, sizeof(msg->data.wifi_state.ip) - 1);
        msg->data.wifi_state.ip[sizeof(msg->data.wifi_state.ip) - 1] = '\0';
    }

    // gateway
    item = cJSON_GetObjectItem(data, "gateway");
    if (cJSON_IsString(item) && item->valuestring)
    {
        strncpy(msg->data.wifi_state.gateway, item->valuestring, sizeof(msg->data.wifi_state.gateway) - 1);
        msg->data.wifi_state.gateway[sizeof(msg->data.wifi_state.gateway) - 1] = '\0';
    }

    // subnet
    item = cJSON_GetObjectItem(data, "subnet");
    if (cJSON_IsString(item) && item->valuestring)
    {
        strncpy(msg->data.wifi_state.subnet, item->valuestring, sizeof(msg->data.wifi_state.subnet) - 1);
        msg->data.wifi_state.subnet[sizeof(msg->data.wifi_state.subnet) - 1] = '\0';
    }

    // mac
    item = cJSON_GetObjectItem(data, "mac");
    if (cJSON_IsString(item) && item->valuestring)
    {
        strncpy(msg->data.wifi_state.mac, item->valuestring, sizeof(msg->data.wifi_state.mac) - 1);
        msg->data.wifi_state.mac[sizeof(msg->data.wifi_state.mac) - 1] = '\0';
    }

    // channel
    item = cJSON_GetObjectItem(data, "channel");
    if (cJSON_IsNumber(item))
        msg->data.wifi_state.channel = (uint8_t)item->valueint;
}
