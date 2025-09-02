#include "mqtt_client.h"

void matt_message_handle(const MqttMessage_t *msg)
{
    if (!msg)
        return;
    
    switch (msg->type)
    {
        case MQTT_MSG_CONTROL:
            
            break;

        default:
            break;
    }
}