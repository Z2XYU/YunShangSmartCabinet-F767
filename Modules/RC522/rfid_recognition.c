#include "rfid_recognition.h"
#include "stdio.h"

uint8_t key_a[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
uint8_t key_b[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

uint8_t block_addr = 0x01;

static void rfid_card_state_clear(RFIDCard_t *card)
{
    card->state = RC522_ERR;
}

int rfid_card_recognition(uint8_t clothes_id)
{
    RFIDCard_t card = {0};

    /*寻卡*/
    card.state = RC522_Request(PICC_REQALL, card.ct);
    /*防冲撞*/
    if (!card.state)
    {
        rfid_card_state_clear(&card);
        card.state = RC522_Anticoll(card.id);
    }
    /*选卡*/
    if (!card.state)
    {
        rfid_card_state_clear(&card);
        printf("卡的类型为：%x%x%x\r\n", card.ct[0], card.ct[1], card.ct[2]); // 读取卡的类型 //读取卡的类型
        printf("卡号：%x-%x-%x-%x\r\n", card.id[0], card.id[1], card.id[2], card.id[3]);
        card.state = RC522_Select(card.id);
    }
    /*验证密钥*/
    if (!card.state)
    {
        rfid_card_state_clear(&card);
        card.state = RC522_AuthState(PICC_AUTHENT1A, block_addr, key_a, card.id);
        if (card.state != RC522_OK)
        {
            printf("密钥A验证失败\r\n");
            return -1;
        }

        card.state = RC522_AuthState(PICC_AUTHENT1B, block_addr, key_b, card.id);
        if (card.state != RC522_OK)
        {
            printf("密钥B验证失败\r\n");
            return -1;
        }
    }
    /*读取块*/
    if (!card.state)
    {
        rfid_card_state_clear(&card);
        card.state = RC522_ReadBlock(block_addr, card.data);
        if (card.state != RC522_OK)
        {
            printf("读块失败\r\n");
            return -1;
        }

        for (uint8_t i = 0; i < 16; i++)
        {
            printf("%02x ", card.data[i]);
        }
        printf("\n");

        if (clothes_id == card.data[0])
        {
            /*信号量*/
            printf("汉服识别成功\r\n");
        }
        else
        {
            printf("汉服识别失败\r\n");
            return -1;
        }
    }
    return 0;
}
