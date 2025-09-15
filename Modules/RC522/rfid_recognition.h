#pragma once

#include "main.h"
#include "rc522.h"

typedef struct
{
    uint8_t id[5];
    uint8_t ct[3];
    uint8_t data[16];
    uint8_t state;
} RFIDCard_t;

int rfid_card_recognition(uint8_t clothes_id);


