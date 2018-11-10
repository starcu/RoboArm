#include <Servo.h>
#include <stdint-gcc.h>

Servo::Servo(uint8_t _gpio, uint16_t initWidth): gpio(_gpio), width(initWidth)
{
    wiringPiSetupGpio();
    pinMode (gpio, PWM_OUTPUT) ;
    pwmSetMode (PWM_MODE_MS);
    pwmSetRange (20000); // 20ms default values
    pwmSetClock (19);
}

void Servo::setWidth(const uint16_t w)
{
    if(w < MIN_WIDTH)
        width = MIN_WIDTH;
    else if(w > MAX_WIDTH)
        width = MAX_WIDTH;
    else
        width = w;

    pwmWrite(gpio, width);
}

uint16_t Servo::getWidth() const
{
    return width;
}