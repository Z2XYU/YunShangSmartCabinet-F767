#pragma once

#include "main.h"
#include "mqtt_types.h"


void mqtt_init(char *id, char *username, char *password, char *server, char* port, char* keepalive);
void mqtt_connect(void);

void mqtt_subscribe_tpoic(const char *topic, const char *qos);
void mqtt_publish(const char* topic ,char *payload);
