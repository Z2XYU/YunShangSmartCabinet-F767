#include "wifi_handler.h"
#include <string.h>
#include "cJSON.h"
#include <stdio.h>

// --------------------------- JSON 辅助函数 ---------------------------

// 安全拷贝 JSON 字符串到目标缓冲区
static void copy_json_string(cJSON *data, const char *key, char *dst, size_t size)
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

// --------------------------- WIFI 状态处理 ---------------------------
static void wifi_status_handle(WifiMessage_t *msg, cJSON *data)
{
    if (!msg || !data)
        return;

    // 只更新 JSON 中存在的字段，避免覆盖原有数据
    cJSON *item = cJSON_GetObjectItem(data, "status");
    if (cJSON_IsNumber(item))
        msg->data.wifi_state.status = (WifiStatus_t)item->valueint;

    copy_json_string(data, "ssid", msg->data.wifi_state.ssid, sizeof(msg->data.wifi_state.ssid));
    copy_json_string(data, "bssid", msg->data.wifi_state.bssid, sizeof(msg->data.wifi_state.bssid));
    copy_json_string(data, "local_ip", msg->data.wifi_state.ip, sizeof(msg->data.wifi_state.ip));
    copy_json_string(data, "gateway", msg->data.wifi_state.gateway, sizeof(msg->data.wifi_state.gateway));
    copy_json_string(data, "subnet", msg->data.wifi_state.subnet, sizeof(msg->data.wifi_state.subnet));
    copy_json_string(data, "mac", msg->data.wifi_state.mac, sizeof(msg->data.wifi_state.mac));
}

// --------------------------- 消息解析 ---------------------------
void wifi_msg_parse(WifiMessage_t *msg, const char *json_str)
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

    // 根据 wifi_cmd 类型调用对应处理函数
    switch (msg->cmd.wifi_cmd)
    {
    case WIFI_CMD_SET_STATUS:
        wifi_status_handle(msg, data);
        break;

    default:
        break;
    }

    cJSON_Delete(root);
}

// --------------------------- 接收消息处理 ---------------------------
void wifi_recv_msg(WifiMessage_t *msg)
{
    if (!msg)
        return;

    switch (msg->cmd.wifi_cmd)
    {
    case WIFI_CMD_CONNECTED:
        clock_get_time();
        break;
    default:
        // 其他命令可添加处理逻辑
        break;
    }
}

// --------------------------- WIFI 命令生成示例 ---------------------------

void wifi_connect_pack(WifiCommand_t *msg, cJSON *root)
{
    if (!msg || !root)
        return;

    cJSON *data = cJSON_CreateObject();
    if (data)
    {
        cJSON_AddStringToObject(data, "ssid", msg->data.wifi_config.ssid);
        cJSON_AddStringToObject(data, "password", msg->data.wifi_config.password);
        cJSON_AddItemToObject(root, "data", data);
    }
}

void wifi_disconnect_pack(WifiCommand_t *msg, cJSON *root)
{
    if (!msg || !root)
        return;

    cJSON *data = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "data", data);
}

void wifi_get_status_pack(WifiCommand_t *msg, cJSON *root)
{
    if (!msg || !root)
        return;

    cJSON *data = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "data", data);
}
