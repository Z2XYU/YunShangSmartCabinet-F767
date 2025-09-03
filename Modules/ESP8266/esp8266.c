#include "esp8266.h"
#include "string.h"
#include "cJSON.h"
#include "usart.h"

static WifiHandle_t wifi;

static char uart_buf[WIFI_UART_BUF_LEN]; // UART 发送缓冲区

static void uart_send_data(const char *str)
{
    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)str, (uint16_t)strlen(str));
}
// 初始化 WiFi 控制结构体
void wifi_init(const char *ssid, const char *password)
{
    memset(&wifi, 0, sizeof(WifiHandle_t));
    wifi.state.status = WIFI_STATUS_DISCONNECTED;
    strcpy(wifi.state.ip, "0.0.0.0");
    wifi.state.signal_strength = 0;
    wifi.state.last_connect_time = 0;
    wifi.state.retry_count = 0;

    strcpy(wifi.config.ssid, ssid);
    strcpy(wifi.config.password, password);
}

// 连接 WiFi
int wifi_connect(void)
{
    cJSON *root = cJSON_CreateObject();
    if (!root)
        return -1;

    cJSON_AddStringToObject(root, "ssid", wifi.config.ssid);
    cJSON_AddStringToObject(root, "password", wifi.config.password);
    cJSON_AddStringToObject(root,"command","wifi_connect");

    // 转换成字符串
    char *json_str = cJSON_PrintUnformatted(root);
    if (!json_str)
    {
        cJSON_Delete(root);
        return -1;
    }

    int len = strlen(json_str);
    if(len >= sizeof(uart_buf) - 2) len = sizeof(uart_buf) - 2;
    strncpy(uart_buf, json_str, len);
    
    uart_buf[len] = '\n';     
    uart_buf[len + 1] = '\0'; 

    uart_send_data(uart_buf);

    cJSON_free(json_str);
    cJSON_Delete(root);

    return 0;
}
