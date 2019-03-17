#include "PCA9685.h"


const PCA9685& PCA9685::writeToChannel(uint16_t ch)
{
	currActiveChannel = ch;
	return *this;
}

void PCA9685::setWidth(uint16_t w)
{
	//I2CWRITE(currActiveChannel, w);
}

void PCA9685::init()
{
	//I2CWRITE(initcommand);
}
