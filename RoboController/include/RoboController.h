//
// Created by Lukas on 10.11.2018.
//

#ifndef ROBOCONTROLLER_ROBOCONTROLLER_H
#define ROBOCONTROLLER_ROBOCONTROLLER_H

#ifndef BCM2835_NO_DELAY_COMPATIBILITY
    #define BCM2835_NO_DELAY_COMPATIBILITY
#endif

#include <thread>
#include <array>
#include "server.h"
#include "Multiplexer.h"
#include "Servo.h"
#include "MPU6050Class.h"

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
    SimpleSocketServer server{8080, "127.0.0.1"};

    RoboState   state = RoboState::OK;

    Servo       servo{SERVO_PWM_PIN};
    MPU         mpu;

    Multiplexer mpuMux;
    Multiplexer servoMux;

    std::thread serverThread;
    std::thread mpuMuxThread;
    std::thread servoMuxThread;

    void serverWorker();
    void mpuWorker();
    void servoWorker();
};

#endif //ROBOCONTROLLER_ROBOCONTROLLER_H