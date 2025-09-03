#include "esp8266.h"
#include "string.h"
#include "cJSON.h"
#include "usart.h"
#include "cmsis_os2.h"
#include "wifi_tasks.h"
#include "wifi_comm.h"
#include "string.h"

static WifiHandle_t wifi;

// 初始化 WiFi 控制结构体
void wifi_init(const char *ssid, const char *password)
{
    memset(&wifi, 0, sizeof(WifiHandle_t));
    wifi.state.status = WL_IDLE_STATUS;
    strcpy(wifi.state.ip, "0.0.0.0");
    strcpy(wifi.config.ssid, ssid);
    strcpy(wifi.config.password, password);
}

// 连接 WiFi
void wifi_connect(void)
{
    WifiCommand_t msg = {0};

    strncpy(msg.type, "wifi", sizeof(msg.type) - 1);
    strncpy(msg.cmd, "wifi_connect", sizeof(msg.cmd) - 1);
    strncpy(msg.data.wifi_config.ssid, wifi.config.ssid, sizeof(msg.data.wifi_config.ssid) - 1);
    strncpy(msg.data.wifi_config.password, wifi.config.password, sizeof(msg.data.wifi_config.password) - 1);

    wifi_send_msg_to_queue(&msg, 10);
}

void wifi_status_update(void)
{
    WifiCommand_t command = {0}; // 初始化为0
    strncpy(command.type, "wifi", sizeof(command.type) - 1);
    strncpy(command.cmd, "wifi_get_status", sizeof(command.cmd) - 1);
    wifi_send_msg_to_queue(&command, 10);
}

void wifi_set_status(WifiState_t *state)
{
    wifi.state.status = state->status;
    strcpy(wifi.state.ssid, state->ssid);
    strcpy(wifi.state.bssid, state->bssid);
    wifi.state.signal_strength = state->signal_strength;
    strcpy(wifi.state.ip, state->ip);
    strcpy(wifi.state.gateway, state->gateway);
    strcpy(wifi.state.subnet, state->subnet);
    strcpy(wifi.state.mac, state->mac);
    wifi.state.channel = state->channel;
}

WifiState_t wifi_get_status(void)
{
    return wifi.state;
}
