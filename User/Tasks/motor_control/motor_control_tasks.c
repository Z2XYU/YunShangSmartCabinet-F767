#include "motor_control_task.h"
#include "wifi_comm.h"
#include <string.h>
#include "tim.h"

osMessageQueueId_t motorControlMsgQueueHandle; 
const osMessageQueueAttr_t motorControlMsgQueue_attributes = {
    .name = "motorControlMsgQueue",
};

osThreadId_t motorControlTaskHandle; 
const osThreadAttr_t motorControlTask_attributes = {
    .name = "motorControlTask",
    .stack_size = 128 * 12, 
    .priority = (osPriority_t)osPriorityHigh,
};

// 定义两个电机
StepperMotor_t motors[2];

static void init_motors(void)
{
    stepper_motor_init(&motors[0], MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin,
                       MOTOR1_STEP_GPIO_Port, MOTOR1_STEP_Pin,
                       NULL, 0,
                       &htim6);

    stepper_motor_init(&motors[1], MOTOR2_DIR_GPIO_Port, MOTOR1_DIR_Pin,
                       MOTOR2_STEP_GPIO_Port, MOTOR2_STEP_Pin,
                       NULL, 0,
                       &htim7);
}

void motor_control_tasks_init(void)
{

    init_motors();
    motorControlMsgQueueHandle = osMessageQueueNew(10,sizeof(WifiMessage_t),&motorControlMsgQueue_attributes);

    motorControlTaskHandle = osThreadNew(motorControlTask,NULL,&motorControlTask_attributes);
}

void motorControlTask(void *argument)
{

    stepper_motor_move_steps(&motors[0],-8000,2000,2000,2000);
    while (1)
    {
        WifiMessage_t msg={0};
        if(osMessageQueueGet(motorControlMsgQueueHandle,&msg,NULL,osWaitForever)==osOK)
        {
            
        }
    }
}
