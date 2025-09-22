#pragma once

#include "main.h"
#include "wifi_comm.h"

void socket_msg_parse(WifiMessage_t *msg, const char *json_str);
void socket_recv_msg(WifiMessage_t *msg);