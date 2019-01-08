#include "PCA9685.h"


void PCA9685::maintainChannel(uint16_t ch);
{
	currChannel = ch;
}

void PCA9685::setChannelWidth(uint16_t w)
{
	//I2CWRITE(currChannel, w);
}

void PCA9685::stop()
{
	this->init();
}

void PCA9685::stop()
{
	this->setChannelWidth(0);
}

void PCA9685::init()
{
	//I2CWRITE(initcommand);
}
