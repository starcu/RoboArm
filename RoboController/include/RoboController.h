//
// Created by Lukas on 10.11.2018.
//

#ifndef ROBOCONTROLLER_ROBOCONTROLLER_H
#define ROBOCONTROLLER_ROBOCONTROLLER_H

#include <thread>
#include <array>
#include "server.h"
#include "Multiplexer.h"
#include "Servo.h"
//#include "I2Cdev.h"
#include "MPU6050.h"

#define SERVO_PWM_PIN 18
#define SERVO_PWM_MUX_S0 1
#define SERVO_PWM_MUX_S1 1
#define SERVO_PWM_MUX_S2 1

#define MPU_MUX_S0 1
#define MPU_MUX_S1 1
#define MPU_MUX_S2 1

enum class RoboState
{
    OK,
    WARNING,
    ERROR
};

class Robo
{
public:
    Robo();

private:
    Servo       servo{SERVO_PWM_PIN};

    //MPU6050 accelgyro;
    //int16_t ax, ay, az;
    //int16_t gx, gy, gz;

    Multiplexer mpuMux;
    Multiplexer servoMux;

    std::thread socketThread;
    std::thread mpuMuxThread;
    std::thread servoMuxThread;
    RoboState   state = OK;
};

#endif //ROBOCONTROLLER_ROBOCONTROLLER_H