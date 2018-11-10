#include "RoboController.h"

Robo::Robo()
{
    mpuMux
    .setCtrlPins(17,27,22)
    ->addStateToQueue(LOW,LOW,LOW)
    ->addStateToQueue(HIGH,LOW,LOW)
    ->addStateToQueue(LOW,HIGH,LOW)
    ->begin();
}