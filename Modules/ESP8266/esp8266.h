#pragma once

#include "main.h"
#include "mqtt_types.h"

// ================== 配置宏 ==================
#define WIFI_SSID_MAX_LEN 32     // WiFi 名称最大长度
#define WIFI_PASSWORD_MAX_LEN 32 // WiFi 密码最大长度

#define WIFI_UART_BUF_LEN 128

// ================== WiFi 状态枚举 ==================
typedef enum
{
    WL_NO_SHIELD = 255, // for compatibility with WiFi Shield library
    WL_IDLE_STATUS = 0,
    WL_NO_SSID_AVAIL = 1,
    WL_SCAN_COMPLETED = 2,
    WL_CONNECTED = 3,
    WL_CONNECT_FAILED = 4,
    WL_CONNECTION_LOST = 5,
    WL_WRONG_PASSWORD = 6,
    WL_DISCONNECTED = 7
} WifiStatus_t;

// ================== WiFi 状态结构体 ==================
typedef struct
{
    int8_t signal_strength;
    uint8_t channel;
    WifiStatus_t status;  
    char ssid[32];
    char bssid[18];
    char ip[16];
    char gateway[16];
    char subnet[16];
    char mac[18];
} WifiState_t;
// ================== WiFi 配置结构体 ==================
typedef struct
{
    char ssid[WIFI_SSID_MAX_LEN];         // WiFi 名称
    char password[WIFI_PASSWORD_MAX_LEN]; // WiFi 密码
} WifiConfig_t;

// ================== WiFi 控制句柄 ==================
typedef struct
{
    WifiState_t state;                          // 当前状态信息
    WifiConfig_t config;                        // 配置信息
    void (*event_callback)(WifiState_t *state); // 状态变化回调
} WifiHandle_t;

// ================== 配置宏 ==================
#define MQTT_CLIENT_ID_MAX_LEN 32   // 客户端 ID 最大长度
#define MQTT_USERNAME_MAX_LEN 32    // 用户名最大长度
#define MQTT_PASSWORD_MAX_LEN 32    // 密码最大长度
#define MQTT_SERVER_ADDR_MAX_LEN 64 // 服务器地址最大长度
#define MQTT_TOPIC_MAX_LEN 64       // 主题最大长度
#define MQTT_PAYLOAD_MAX_LEN 256    // 消息最大长度

// ================== MQTT 状态枚举 ==================
typedef enum
{
    MQTT_STATUS_DISCONNECTED = 0, // 未连接
    MQTT_STATUS_CONNECTING,       // 正在连接
    MQTT_STATUS_CONNECTED,        // 已连接
    MQTT_STATUS_SUBSCRIBED,       // 已订阅
    MQTT_STATUS_ERROR             // 出错
} MqttStatus_e;

// ================== MQTT 状态结构体 ==================
typedef struct
{
    MqttStatus_e status;        // 当前状态
    uint32_t last_connect_time; // 上次连接时间
    uint8_t retry_count;        // 重试次数
} MqttState_t;

// ================== MQTT 控制句柄 ==================
typedef struct
{
    MqttState_t state;                          // 状态信息
    MqttConfig_t config;                        // 配置信息
    void (*event_callback)(MqttMessage_t *msg); // 收到消息时的回调
} MqttHandle_t;

void wifi_init(const char *ssid, const char *password);
void wifi_connect(void);
WifiState_t wifi_get_status(void);
void wifi_status_update(void);
void wifi_set_status(WifiState_t *state);