#pragma once

#include "main.h"

// ================== 配置宏 ==================
#define WIFI_SSID_MAX_LEN      32   // WiFi 名称最大长度
#define WIFI_PASSWORD_MAX_LEN  32   // WiFi 密码最大长度

#define WIFI_UART_BUF_LEN    128

// ================== WiFi 状态枚举 ==================
typedef enum
{
    WIFI_STATUS_DISCONNECTED = 0,  // 未连接
    WIFI_STATUS_CONNECTING,        // 正在连接
    WIFI_STATUS_CONNECTED,         // 已连接
    WIFI_STATUS_FAILED             // 连接失败
} WifiStatus_e;

// ================== WiFi 状态结构体 ==================
typedef struct
{
    WifiStatus_e status;                 // 当前状态
    char ip[16];                         // IP 地址
    int signal_strength;                 // 信号强度（RSSI）
    uint32_t last_connect_time;          // 上次连接时间（毫秒）
    uint8_t retry_count;                 // 重试次数
} WifiState_t;

// ================== WiFi 配置结构体 ==================
typedef struct
{
    char ssid[WIFI_SSID_MAX_LEN];        // WiFi 名称
    char password[WIFI_PASSWORD_MAX_LEN];// WiFi 密码
} WifiConfig_t;

// ================== WiFi 控制句柄 ==================
typedef struct
{
    WifiState_t state;                   // 当前状态信息
    WifiConfig_t config;                 // 配置信息
    void (*event_callback)(WifiState_t *state); // 状态变化回调
} WifiHandle_t;



// ================== 配置宏 ==================
#define MQTT_CLIENT_ID_MAX_LEN   32    // 客户端 ID 最大长度
#define MQTT_USERNAME_MAX_LEN    32    // 用户名最大长度
#define MQTT_PASSWORD_MAX_LEN    32    // 密码最大长度
#define MQTT_SERVER_ADDR_MAX_LEN 64    // 服务器地址最大长度
#define MQTT_TOPIC_MAX_LEN       64    // 主题最大长度
#define MQTT_PAYLOAD_MAX_LEN     256   // 消息最大长度

// ================== MQTT 状态枚举 ==================
typedef enum
{
    MQTT_STATUS_DISCONNECTED = 0,   // 未连接
    MQTT_STATUS_CONNECTING,         // 正在连接
    MQTT_STATUS_CONNECTED,          // 已连接
    MQTT_STATUS_SUBSCRIBED,         // 已订阅
    MQTT_STATUS_ERROR               // 出错
} MqttStatus_e;

// ================== MQTT 状态结构体 ==================
typedef struct
{
    MqttStatus_e status;                 // 当前状态
    uint32_t last_connect_time;          // 上次连接时间
    uint8_t retry_count;                 // 重试次数
} MqttState_t;

// ================== MQTT 配置结构体 ==================
typedef struct
{
    char client_id[MQTT_CLIENT_ID_MAX_LEN];   // 客户端 ID
    char username[MQTT_USERNAME_MAX_LEN];     // 用户名
    char password[MQTT_PASSWORD_MAX_LEN];     // 密码
    char server[MQTT_SERVER_ADDR_MAX_LEN];    // 服务器地址
    uint16_t port;                            // 服务器端口
    char sub_topic[MQTT_TOPIC_MAX_LEN];       // 订阅主题
    char pub_topic[MQTT_TOPIC_MAX_LEN];       // 发布主题
} MqttConfig_t;

// ================== MQTT 消息结构体 ==================
typedef struct
{
    char topic[MQTT_TOPIC_MAX_LEN];       // 消息主题
    char payload[MQTT_PAYLOAD_MAX_LEN];   // 消息内容
    uint16_t length;                      // 消息长度
    uint8_t qos;                          // QoS 等级
    uint8_t retain;                       // 是否保留
} MqttMessage_t;

// ================== MQTT 控制句柄 ==================
typedef struct
{
    MqttState_t state;                    // 状态信息
    MqttConfig_t config;                  // 配置信息
    void (*event_callback)(MqttMessage_t *msg); // 收到消息时的回调
} MqttHandle_t;
