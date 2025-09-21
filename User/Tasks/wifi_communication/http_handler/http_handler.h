#pragma once

#include "main.h"
#include "wifi_comm.h"

void get_beijing_time_pack(WifiCommand_t *msg, cJSON *root);
void http_recv_msg(WifiMessage_t *msg);
void http_msg_parse(WifiMessage_t *msg, const char *json_str);