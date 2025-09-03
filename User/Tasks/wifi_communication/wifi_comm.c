#include "wifi_comm.h"
#include "wifi_tasks.h"
#include "usart.h"
#include "string.h"
#include "cJSON.h"

static char uart_buf[512];

// 向消息队列发送消息
osStatus_t wifi_send_msg_to_queue(osMessageQueueId_t queue, const WifiCommand_t *cmd, uint32_t timeout_ms)
{
    if (queue == NULL) // 使用传入的句柄判断
        return osErrorParameter;

    return osMessageQueuePut(
        queue, // 使用传入的队列
        cmd,
        0,         // 优先级
        timeout_ms // 超时
    );
}


static void msg_send(const char *json_str)
{
    if(json_str == NULL) return;
    
    size_t len = strlen(json_str);
    if(len == 0 || len > sizeof(uart_buf)-2) return;

    // 等待上一条 DMA 发送完成
    while(HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY) osDelay(1);

    strcpy(uart_buf, json_str);
    uart_buf[len] = '\n';       // 添加换行
    uart_buf[len+1] = '\0';

    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)uart_buf, (uint16_t)(len+1));
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
            cJSON_AddStringToObject(root, "ssid", msg->payload.wifi_config.ssid);
            cJSON_AddStringToObject(root, "password", msg->payload.wifi_config.password);
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

    if(strcmp(msg->type,"wifi")==0)
    {
        if(strcmp(msg->cmd,"wifi_status_update")==0)
        {
            wifi_set_status(&msg->payload.wifi_state);
        }
    }
}
