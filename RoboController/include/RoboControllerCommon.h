//
// Created by Lukas on 15.12.2018.
//

#ifndef ROBOCONTROLLER_ROBOCONTROLLERCOMMON_H
#define ROBOCONTROLLER_ROBOCONTROLLERCOMMON_H

#ifndef BCM2835_NO_DELAY_COMPATIBILITY
    #define BCM2835_NO_DELAY_COMPATIBILITY
#endif

#include <thread>
#include <atomic>
#include "server.h"
#include "Multiplexer.h"
#include "Servo.h"
#include "MPU6050Class.h"
#include "RoboLogger.h"

#define SERVO_PIN 18
#define SERVO_MUX_S0 5
#define SERVO_MUX_S1 6
#define SERVO_MUX_S2 13
#define SERVO_MUX_ENABLE_PIN 999
#define SERVO_MUX_WORKER_POLL_INTERVAL_MS 10
#define SERVO_MUX_SWITCHING_INTERVAL_MS 120

#define MPU_MUX_S0 17
#define MPU_MUX_S1 27
#define MPU_MUX_S2 22
#define MPU_MUX_ENABLE_PIN 1001
#define MPU_MUX_WORKER_POLL_INTERVAL_MS 20

enum class RoboState
{
    UNINITIALIZED,
    OK,
    WARNING,
    ERROR
};

inline std::string RoboStateToString(RoboState s)
{
    switch(s)
    {
        case RoboState::UNINITIALIZED:
            return "UNINITIALIZED";
        case RoboState::OK:
            return "OK";
        case RoboState::WARNING:
            return "WARNING";
        case RoboState::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

struct accel
{
    int16_t x=0;
    int16_t y=0;
    int16_t z=0;
};

struct gyro
{
    int16_t x=0;
    int16_t y=0;
    int16_t z=0;
};


struct magnet
{
    int16_t x=0;
    int16_t y=0;
    int16_t z=0;
};

#endif // ROBOCONTROLLER_ROBOCONTROLLERCOMMON_H