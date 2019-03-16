class PCA9685
{
public:
	PCA9685(): currChannel(0) {}

	const PCA9685& writeToChannel(uint16_t ch);
	void setWidth(uint16_t w);
	void start();
	void stop();

private:
	void init();
	
	uint16_t currChannel;
};