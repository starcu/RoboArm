#include <stdint.h>
#include <thread>
#include <chrono>

class PCA9685
{
public:
	PCA9685(uint16_t mch): currActiveChannel(0), MAX_USABLE_CHANNELS(mch)
	{
		this->init();
	}

	~PCA9685()
	{
		for(int i=0; i<MAX_USABLE_CHANNELS; ++i)
	    	{
	    		this->writeToChannel(i)->setWidth(0);
	    		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	    	}
	}

	const PCA9685& writeToChannel(uint16_t ch);
	void setWidth(uint16_t w);
	void start();
	void stop();

private:
	void init();
	
	uint16_t currActiveChannel;
	const uint16_t MAX_USABLE_CHANNELS;
};
