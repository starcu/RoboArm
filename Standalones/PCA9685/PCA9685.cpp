#include "PCA9685.h"


const PCA9685& PCA9685::writeToChannel(uint16_t ch);
{
	currChannel = ch;
	return *this;
}

void PCA9685::setWidth(uint16_t w)
{
	//I2CWRITE(currChannel, w);
}

void PCA9685::start()
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
