#pragma once

#include "main.h"
#include "wifi_comm.h"

void mqtt_connect_pack(WifiCommand_t *msg, cJSON *root);
void mqtt_subscribe_pcak(WifiCommand_t *msg, cJSON *root);
void mqtt_publish_pack(WifiCommand_t *msg, cJSON *root);

void mqtt_recv_msg(WifiMessage_t *msg);