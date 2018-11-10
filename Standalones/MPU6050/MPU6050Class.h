#include <stdio.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <math.h>
#include <iostream>

class MPU
{
public:
    MPU()
    {
        I2Cdev::initialize();
        accelgyro.initialize();
    }

    void getMeasueremnts()
    {
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    }

    int16_t getAccelX() const { return ax; }
    int16_t getAccelY() const { return ay; }
    int16_t getAccelZ() const { return az; }

    int16_t getGyroX() const { return gx; }
    int16_t getGyroY() const { return gy; }
    int16_t getGyroZ() const { return gz; }

private:
    MPU6050 accelgyro;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
};
