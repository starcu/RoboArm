/*
To compile on a Raspberry Pi (1 or 2)
  1. install the bcm2835 library, see http://www.airspayce.com/mikem/bcm2835/index.html
  2. enable i2c on your RPi , see https://learn.adafruit.com/adafruits-raspberry-pi-lesson-4-gpio-setup/configuring-i2c
  3. connect your i2c devices
  4. then from bash
      $ PATH_I2CDEVLIB=~/i2cdevlib/
      $ gcc -o MPU6050_example_1 ${PATH_I2CDEVLIB}RaspberryPi_bcm2835/MPU6050/examples/MPU6050_example_1.cpp \
         -I ${PATH_I2CDEVLIB}RaspberryPi_bcm2835/I2Cdev ${PATH_I2CDEVLIB}RaspberryPi_bcm2835/I2Cdev/I2Cdev.cpp \
         -I ${PATH_I2CDEVLIB}/Arduino/MPU6050/ ${PATH_I2CDEVLIB}/Arduino/MPU6050/MPU6050.cpp -l bcm2835 -l m
      $ sudo ./MPU6050_example_1

*/

/*
 * author: Lukas
 *
 */

#include <stdio.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <math.h>
#include <iostream>
#include "Multiplexer.h"

int main(int argc, char **argv) 
{
    // use the code below to change accel/gyro offset values
    /*
    printf("Updating internal sensor offsets...\n");
    // -76	-2359	1688	0	0	0
    printf("%i \t %i \t %i \t %i \t %i \t %i\n", 
         accelgyro.getXAccelOffset(),
         accelgyro.getYAccelOffset(),
         accelgyro.getZAccelOffset(),
         accelgyro.getXGyroOffset(),
         accelgyro.getYGyroOffset(),
         accelgyro.getZGyroOffset());
    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
    printf("%i \t %i \t %i \t %i \t %i \t %i\n", 
         accelgyro.getXAccelOffset(),
         accelgyro.getYAccelOffset(),
         accelgyro.getZAccelOffset(),
         accelgyro.getXGyroOffset(),
         accelgyro.getYGyroOffset(),
         accelgyro.getZGyroOffset());
    */
    
    Multiplexer mux;
    
    mux.setCtrlPins(17,27,22)
    ->addStateToQueue(LOW,LOW,LOW)
    ->addStateToQueue(HIGH,LOW,LOW)
    ->addStateToQueue(LOW,HIGH,LOW)
    ->begin();
    
    I2Cdev::initialize();
    MPU6050 accelgyro;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    
    uint64_t muxCounter = 0;
    std::string info;
    
    while (true) 
    {
        accelgyro.initialize();
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        info = "MPU6050 no." +std::to_string(muxCounter%3)+ " is working";
        std::cout << "--- [" << info << "] ---" << std::endl;
        std::cout << "x: " << ax << ", y: " << ay << ", z: " << az << std::endl;
        //mux.nextState();
        //muxCounter++;
        delay(50);
    }
    
    return 1; 
}
