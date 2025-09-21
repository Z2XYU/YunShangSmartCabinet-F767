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
    wifi.state.status = WL_CONNECT_FAILED;
    strcpy(wifi.state.ip, "0.0.0.0");
    strcpy(wifi.config.ssid, ssid);
    strcpy(wifi.config.password, password);
}

// 连接 WiFi
void wifi_connect(void)
{
    WifiCommand_t msg = {0};

    msg.type = TYPE_WIFI;
    msg.cmd.wifi_cmd = WIFI_CMD_CONNECT;

    strncpy(msg.data.wifi_config.ssid, wifi.config.ssid, sizeof(msg.data.wifi_config.ssid) - 1);
    strncpy(msg.data.wifi_config.password, wifi.config.password, sizeof(msg.data.wifi_config.password) - 1);

    wifi_send_msg_to_queue(&msg, 0);
}

void wifi_status_update(void)
{
    WifiCommand_t command = {0}; 

    command.type = TYPE_WIFI;
    command.cmd.wifi_cmd = WIFI_CMD_GET_STATUS;
    wifi_send_msg_to_queue(&command, 0);
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
