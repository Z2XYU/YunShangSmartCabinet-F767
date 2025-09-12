#include "motor_control_tasks.h"
#include "wifi_comm.h"
#include <string.h>
#include "tim.h"
#include "stepper_motor.h"
#include "plasma.h"

osMessageQueueId_t motorControlMsgQueueHandle;
const osMessageQueueAttr_t motorControlMsgQueue_attributes = {
    .name = "motorControlMsgQueue",
};

osThreadId_t motorCalibrationTaskHandle;
const osThreadAttr_t motorCalibrationTask_attributes = {
    .name = " motorExecTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityNormal1,
};

osThreadId_t motorControlTaskHandle;
const osThreadAttr_t motorControlTask_attributes = {
    .name = "motorCommTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityHigh,
};

// 定义两个电机
StepperMotor_t motors[MOTOR_NUM];
MagneticSensor_t sensors[MOTOR_NUM] =
    {
        {ReedSwitch1_GPIO_Port, ReedSwitch1_Pin},
        {ReedSwitch2_GPIO_Port, ReedSwitch2_Pin}};
DoorController_t doors[MOTOR_NUM];

Plasma_t plasmas[2] = {
    {plasmas1_GPIO_Port, plasmas1_Pin},
    {plasmas2_GPIO_Port, plasmas2_Pin}};

static void motors_init(void)
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
static void doors_init(void)
{
    for (int i = 0; i < MOTOR_NUM; i++)
    {
        doors[i].motor = &motors[i];
        doors[i].sensor = &sensors[i];
        doors[i].state = DOOR_IDLE;
        doors[i].sensor_flag = 0;
        doors[i].target_steps = 0;
    }
}

void purification_timer_callback(void *argument)
{
    plasma_off(&plasmas[0]);
    plasma_off(&plasmas[1]);
}

void motor_control_tasks_init(void)
{

    motors_init();
    sensor_init();
    doors_init();

    motorControlMsgQueueHandle = osMessageQueueNew(10, sizeof(WifiMessage_t), &motorControlMsgQueue_attributes);

    // motorCalibrationTaskHandle = osThreadNew(motorCalibrationTask, NULL, &motorCalibrationTask_attributes);
    motorControlTaskHandle = osThreadNew(motorCommTask, NULL, &motorControlTask_attributes);
}

void motorCalibrationTask(void *argument)
{
    while (1)
    {
        osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);

        for (int i = 0; i < MOTOR_NUM; i++)
        {
            DoorController_t *d = &doors[i];

            switch (d->state)
            {
            case DOOR_OPENING:
                doors[i].state = DOOR_IDLE;
                break;

            case DOOR_CLOSEING:
                door_calibration(&doors[i]);
                doors[i].state = DOOR_IDLE;
                break;

            default:
                break;
            }
        }
    }
}

void motorCommTask(void *argument)
{
    while (1)
    {
        WifiMessage_t msg = {0};
        if (osMessageQueueGet(motorControlMsgQueueHandle, &msg, NULL, osWaitForever) == osOK)
        {
            if (strcmp(msg.type, "mqtt") == 0 && strcmp(msg.cmd, "door_control") == 0)
            {
                if (strcmp(msg.data.control_cmd.action, "rent") == 0)
                {
                    if (strcmp(msg.data.control_cmd.option, "open") == 0)
                    {
                        doors[msg.data.control_cmd.cabinet_location].state = DOOR_OPENING;
                        door_open(&motors[msg.data.control_cmd.cabinet_location - 1]);
                    }
                    else if (strcmp(msg.data.control_cmd.option, "close") == 0)
                    {
                        doors[msg.data.control_cmd.cabinet_location].state = DOOR_CLOSEING;
                        door_close(&motors[msg.data.control_cmd.cabinet_location - 1]);
                    }
                }
                else if (strcmp(msg.data.control_cmd.action, "return") == 0)
                {
                }
            }
        }
    }
}
