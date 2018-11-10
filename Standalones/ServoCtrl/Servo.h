#include <wiringPi.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <mutex>
#include <condition_variable>

#define MIN_WIDTH 544
#define MAX_WIDTH 2400

class Servo
{
public:
    Servo(uint8_t _gpio, uint16_t initWidth=MIN_WIDTH);
    Servo(const Servo& s) = delete;

    void setWidth(const uint16_t w);
    uint16_t getWidth() const;

private:
    uint8_t gpio;
    uint16_t width = 0;
};
