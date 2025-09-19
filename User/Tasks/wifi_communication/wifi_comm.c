#include "wifi_comm.h"
#include "wifi_tasks.h"
#include "usart.h"
#include "string.h"
#include "cJSON.h"
#include "stdio.h"
#include "mqtt_message.h"
#include "motor_control_tasks.h"
#include "clock.h"
#include "gui_guider.h"
#include "custom.h"
#include "ui_tasks.h"

static char uart_buf[512];

// 前向声明
static void status_handle(WifiMessage_t *msg, cJSON *data);
static void notice_hanle(WifiMessage_t *msg, cJSON *data);
static void door_control_handle(WifiMessage_t *msg, cJSON *data);
static void beijing_time_handle(WifiMessage_t *msg, cJSON *data);

#define WIFI_CMD_TABLE_SIZE 2
WifiCmdMap_t wifi_cmd_table[] = {
    {"status", status_handle},
    {"notice", notice_hanle},

};

#define MQTT_CMD_TABLE_SIZE 2
MqttCmdMap_t mqtt_cmd_table[] = {
    {"notice", notice_hanle},
    {"door_control", door_control_handle},
};

#define HTTP_CMD_TABLE_SIZE 1
HttpCmdMap_t http_cmd_table[] = {
    {"get_time", beijing_time_handle}};

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

    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)uart_buf, (uint16_t)(len + 1));
    // printf("uart2:%s\n", uart_buf);
}

void wifi_send_message_handle(WifiCommand_t *msg)
{
    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
        return;

    char *out = NULL;
    cJSON_AddStringToObject(root, "type", msg->type);
    cJSON_AddStringToObject(root, "cmd", msg->cmd);

    if (strcmp(msg->type, "wifi") == 0)
    {
        if (strcmp(msg->cmd, "wifi_get_status") == 0)
        {
            // wifi_get_status 没有 data
        }
        else if (strcmp(msg->cmd, "wifi_connect") == 0)
        {
            cJSON *data = cJSON_CreateObject();
            cJSON_AddStringToObject(data, "ssid", msg->data.wifi_config.ssid);
            cJSON_AddStringToObject(data, "password", msg->data.wifi_config.password);
            cJSON_AddItemToObject(root, "data", data);
        }
    }
    else if (strcmp(msg->type, "mqtt") == 0)
    {
        if (strcmp(msg->cmd, "mqtt_connect") == 0)
        {
            cJSON *data = cJSON_CreateObject();
            cJSON_AddStringToObject(data, "client_id", msg->data.mqtt_config.client_id);
            cJSON_AddStringToObject(data, "username", msg->data.mqtt_config.username);
            cJSON_AddStringToObject(data, "password", msg->data.mqtt_config.password);
            cJSON_AddStringToObject(data, "server", msg->data.mqtt_config.server);

            cJSON_AddStringToObject(data, "port", msg->data.mqtt_config.port);
            cJSON_AddStringToObject(data, "keepalive", msg->data.mqtt_config.keepalive);

            cJSON_AddItemToObject(root, "data", data);
        }
        else if (strcmp(msg->cmd, "subscribe") == 0)
        {
            cJSON *data = cJSON_CreateObject();
            cJSON_AddStringToObject(data, "topic", msg->data.mqtt_config.topic);
            cJSON_AddStringToObject(data, "qos", msg->data.mqtt_config.qos);

            cJSON_AddItemToObject(root, "data", data);
        }
        else if (strcmp(msg->cmd, "publish") == 0)
        {
            cJSON *data = cJSON_CreateObject();

            cJSON_AddStringToObject(data, "topic", msg->data.mqtt_config.topic);
            cJSON_AddStringToObject(data, "payload", msg->data.mqtt_config.payload);

            cJSON_AddItemToObject(root, "data", data);
        }
    }
    else if (strcmp(msg->type, "http") == 0)
    {
        if (strcmp(msg->cmd, "get_time") == 0)
        {
            //printf("获取时间命令\n");
        }
    }

    out = cJSON_PrintUnformatted(root);
    if (out != NULL)
    {
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
        else if (strcmp(msg->cmd, "notice") == 0)
        {
            if (strcmp(msg->data.notice, "wifi_connected") == 0)
            {
                mqtt_connect();
                /*获取北京时间*/
                osDelay(100);
                clock_get_time();
            }
        }
    }
    else if (strcmp(msg->type, "mqtt") == 0)
    {
        if (strcmp(msg->cmd, "notice") == 0)
        {
            if (strcmp(msg->data.notice, "mqtt_connected") == 0)
            {
                mqtt_subscribe_tpoic("control", 0);
            }
        }
        else if (strcmp(msg->cmd, "door_control") == 0)
        {
            osMessageQueuePut(motorControlMsgQueueHandle, msg, 0, 0);
        }
    }
    else if (strcmp(msg->type, "http") == 0)
    {
        if (strcmp(msg->cmd, "get_time") == 0)
        {
            clock_set_time(&msg->data.clock);
            //printf("设置时间\n");
            osSemaphoreRelease(systemInitSemaphore);
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
    else if (strcmp(msg->type, "mqtt") == 0)
    {
        cJSON *cmd_item = cJSON_GetObjectItem(root, "cmd");
        if (cJSON_IsString(cmd_item) && cmd_item->valuestring != NULL)
        {
            strncpy(msg->cmd, cmd_item->valuestring, sizeof(msg->cmd) - 1);
            msg->cmd[sizeof(msg->cmd) - 1] = '\0';
        }
        for (size_t i = 0; i < MQTT_CMD_TABLE_SIZE; i++)
        {
            if (strcmp(msg->cmd, mqtt_cmd_table[i].cmd) == 0)
            {
                if (mqtt_cmd_table[i].handler != NULL)
                {
                    cJSON *data_item = cJSON_GetObjectItem(root, "data");
                    mqtt_cmd_table[i].handler(msg, data_item);
                }
                break;
            }
        }
    }
    else if (strcmp(msg->type, "http") == 0)
    {
        cJSON *cmd_item = cJSON_GetObjectItem(root, "cmd");
        if (cJSON_IsString(cmd_item) && cmd_item->valuestring != NULL)
        {
            strncpy(msg->cmd, cmd_item->valuestring, sizeof(msg->cmd) - 1);
            msg->cmd[sizeof(msg->cmd) - 1] = '\0';
        }
        for (size_t i = 0; i < HTTP_CMD_TABLE_SIZE; i++)
        {
            if (strcmp(msg->cmd, http_cmd_table[i].cmd) == 0)
            {
                if (http_cmd_table[i].handler != NULL)
                {
                    cJSON *data_item = cJSON_GetObjectItem(root, "data");
                    http_cmd_table[i].handler(msg, data_item);
                }
                break;
            }
        }
    }

    cJSON_Delete(root);
}

static void beijing_time_handle(WifiMessage_t *msg, cJSON *data)
{
    if (!msg || !data)
        return;
    //printf("处理时间\n");
    if (cJSON_IsString(data))
    {
        int year, month, day, hour, min, sec;
        sscanf(data->valuestring, "%d-%d-%d %d:%d:%d",
               &year, &month, &day, &hour, &min, &sec);

        msg->data.clock.sDate.Year = year - 2000;
        msg->data.clock.sDate.Month = month;
        msg->data.clock.sDate.Date = day;
        msg->data.clock.sTime.Hours = hour;
        msg->data.clock.sTime.Minutes = min;
        msg->data.clock.sTime.Seconds = sec;

        // printf("解析到的时间: %04d-%02d-%02d %02d:%02d:%02d\r\n",
        //        msg->data.clock.sDate.Year,
        //        msg->data.clock.sDate.Month,
        //        msg->data.clock.sDate.Date,
        //        msg->data.clock.sTime.Hours,
        //        msg->data.clock.sTime.Minutes,
        //        msg->data.clock.sTime.Seconds);
    }
}

static void notice_hanle(WifiMessage_t *msg, cJSON *data)
{
    if (!msg || !data)
        return;

    cJSON *item = NULL;
    item = cJSON_GetObjectItem(data, "payload");
    if (cJSON_IsString(item))
    {
        strncpy(msg->data.notice, item->valuestring, sizeof(msg->data.notice) - 1);
        msg->data.notice[sizeof(msg->data.notice) - 1] = '\0';
    }
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

static void door_control_handle(WifiMessage_t *msg, cJSON *data)
{
    if (!msg || !data)
        return;

    cJSON *item = NULL;

    item = cJSON_GetObjectItem(data, "clothes_id");
    if (cJSON_IsNumber(item))
    {
        msg->data.control_cmd.clothes_id = item->valueint;
    }

    item = cJSON_GetObjectItem(data, "action");
    if (cJSON_IsString(item))
    {
        strncpy(msg->data.control_cmd.action, item->valuestring, sizeof(msg->data.control_cmd.action) - 1);
        msg->data.control_cmd.action[sizeof(msg->data.control_cmd.action) - 1] = '\0';
    }

    item = cJSON_GetObjectItem(data, "option");
    if (cJSON_IsString(item))
    {
        strncpy(msg->data.control_cmd.option, item->valuestring, sizeof(msg->data.control_cmd.action) - 1);
        msg->data.control_cmd.action[sizeof(msg->data.control_cmd.action) - 1] = '\0';
    }

    item = cJSON_GetObjectItem(data, "cabinet_location");
    if (cJSON_IsNumber(item))
    {
        msg->data.control_cmd.cabinet_location = item->valueint;
    }
}
