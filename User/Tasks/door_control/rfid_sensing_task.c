#include "rfid_sensing_task.h"
#include "rfid_recognition.h"

osThreadId_t rfidSensingTaskHandle;
const osThreadAttr_t rfidSensingTask_attributes = {
    .name = " rfidSensingTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal1,
};

osMessageQueueId_t rfidQueueHandle;
osSemaphoreId_t recogDoneSemaphoreHandle; // 卡片识别完成信号量

static osTimerId_t timerHandle;

static volatile uint8_t timeoutFlag = 0;

static void timer_callback(void *argument)
{
    timeoutFlag = 1;
}

void rfid_task_init(void)
{
    rfidQueueHandle = osMessageQueueNew(10, sizeof(uint8_t), NULL);
    rfidSensingTaskHandle = osThreadNew(rfidSensingTask, NULL, &rfidSensingTask_attributes);
    timerHandle = osTimerNew(timer_callback, osTimerOnce, NULL, NULL);
    recogDoneSemaphoreHandle = osSemaphoreNew(1, 0, NULL);
}

void rfidSensingTask(void *argument)
{
    RC522_Init();
    while (1)
    {
        uint8_t clothes_id=0;
        if (osMessageQueueGet(rfidQueueHandle, &clothes_id, NULL, osWaitForever) == osOK)
        {
            uint8_t flag = 1;
            osTimerStart(timerHandle, osKernelGetTickFreq() * 10);

            while (1)
            {
                flag = rfid_card_recognition(clothes_id);

                if (flag == RC522_OK)
                {
                    osSemaphoreRelease(recogDoneSemaphoreHandle);
                    break;
                }
                else if (timeoutFlag)
                {
                    timeoutFlag = 0;
                    break;
                }
                osDelay(50);
            }
        }
    }
}