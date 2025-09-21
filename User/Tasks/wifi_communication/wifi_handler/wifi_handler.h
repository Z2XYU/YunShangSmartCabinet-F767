#pragma once

#include "main.h"
#include "wifi_comm.h"

void wifi_connect_pack(WifiCommand_t *msg, cJSON *root);
void wifi_disconnect_pack(WifiCommand_t *msg, cJSON *root);
void wifi_get_status_pack(WifiCommand_t *msg, cJSON *root);

void wifi_msg_parse(WifiMessage_t *msg, const char *json_str);
void wifi_recv_msg(WifiMessage_t *msg);