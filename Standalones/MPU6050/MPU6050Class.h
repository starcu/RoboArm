#include <stdio.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <math.h>
#include <iostream>


class MPU
{
public:
    MPU(bool mag = false): magEnabled(mag)
    {
        I2Cdev::initialize();
        //accelgyro.initialize();
    }

    void initialize()
    {
        accelgyro.initialize();
    }

    void getMeasurements()
    {
        if(!magEnabled)
            accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        else
            accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    }

    int16_t getAccelX() const { return ax; }
    int16_t getAccelY() const { return ay; }
    int16_t getAccelZ() const { return az; }

    int16_t getGyroX() const { return gx; }
    int16_t getGyroY() const { return gy; }
    int16_t getGyroZ() const { return gz; }

    int16_t getMagnetX() const { return mx; }
    int16_t getMagnetY() const { return my; }
    int16_t getMagnetZ() const { return mz; }

private:
    MPU6050 accelgyro;
    bool magEnabled = false;

    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t mx, my, mz;
};
