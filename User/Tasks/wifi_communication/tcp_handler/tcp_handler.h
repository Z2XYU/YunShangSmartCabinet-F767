#pragma once

#include "main.h"
#include "wifi_comm.h"

void tcp_msg_parse(WifiMessage_t *msg, const char *json_str);
void tcp_recv_msg(WifiMessage_t *msg);