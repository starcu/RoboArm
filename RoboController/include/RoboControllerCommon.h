//
// Created by Lukas on 15.12.2018.
//

#ifndef ROBOCONTROLLER_ROBOCONTROLLERCOMMON_H
#define ROBOCONTROLLER_ROBOCONTROLLERCOMMON_H

#ifndef BCM2835_NO_DELAY_COMPATIBILITY
    #define BCM2835_NO_DELAY_COMPATIBILITY
#endif

#define FUNCTION_NAME std::string(__func__)

/*
#define SERVO_PIN 18
#define SERVO_MUX_S0 5
#define SERVO_MUX_S1 6
#define SERVO_MUX_S2 13
#define SERVO_MUX_ENABLE_PIN 999
#define SERVO_MUX_SWITCHING_INTERVAL_MS 120


// servo worker defines
#define SERVO_WORKER_POLL_INTERVAL_MS 10

// mpu worker defines
#define MPU_MUX_S0 17
#define MPU_MUX_S1 27
#define MPU_MUX_S2 22
#define MPU_MUX_ENABLE_PIN 1001
#define MPU_WORKER_POLL_INTERVAL_MS 20
*/

// i2c worker defines
#define I2C_MUX_S0 17
#define I2C_MUX_S1 27
#define I2C_MUX_S2 22
#define I2C_MUX_ENABLE_PIN 999
#define I2C_WORKER_POLL_INTERVAL_MS 20

/*
  MUX OUTPUTS

 m0 m1 m2 m3 pca
 ______________
 |  |  |  |   |
 |--------|  |--|
  MPU bus    PCA BUS
 4 devices   1 device

*/

namespace RoboI2CBuses
{
    #define MPU_I2C_BUS 0
    #define PCA9685_I2C_BUS 1
}

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