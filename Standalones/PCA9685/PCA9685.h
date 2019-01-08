class PCA9685
{
public:
	PCA9685(): currChannel(0) {}

	void maintainChannel(uint16_t ch);
	void setChannelWidth(uint16_t w);
	void start();
	void stop();

private:
	void init();
	
	uint16_t currChannel;
};