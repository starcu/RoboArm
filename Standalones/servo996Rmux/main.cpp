#include <wiringPi.h>
#include <stdio.h>
#include <string>
#include <bcm2835.h>
#include <iostream>


#define RANGE_MIN 544
#define RANGE_MAX 2400

int main (int argc, char** argv)
{
    //PWM
    wiringPiSetupGpio();
    pinMode (18, PWM_OUTPUT) ;
    pwmSetMode (PWM_MODE_MS);
    pwmSetRange (20000);
    pwmSetClock (19.2);

    int pWidth = 0; // minimum 0.5444ms
    int timeout = 1;
    bool timeoutSet = false;

    try
    {
       pWidth = std::stoi(argv[1]);
    } 
    catch(...)
    {
       printf("Pulse width not set! Exiting...\n");
       exit(0);
    }

    if(pWidth < RANGE_MIN || pWidth > RANGE_MAX)
    {
        printf("Pulse width (%d) out of range (%d, %d)! Exiting...t\n", pWidth, RANGE_MIN, RANGE_MAX);
        exit(0);
    }

    try
    {
       timeout = std::stoi(argv[2]);
       timeoutSet = true;
       printf("Timeout set to %ds\n", timeout);
    } 
    catch(...)
    {
        printf("Timeout not set, inf. mode on\n");
       //timeout = 1;
    }

    // MUX
    bcm2835_init();
    bcm2835_gpio_fsel(5, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(6, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(13, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_delay(100);
    
    int outNum = -1;
    try
    {
       outNum = std::stoi(argv[3]);
       printf("MUX out set to %d\n", outNum);
    
        if(outNum < 0)
            printf("MUX out not set.\n");

        if(outNum > 5)
            printf("MUX output number out of range (0,5).\n");
    
    } 
    catch(...)
    {
        printf("MUX out not set.\n");
        outNum = -1;
       //timeout = 1;
    }
       
    if(outNum == 0)
    {
        std::cout << "OUT no.0" << std::endl;
        bcm2835_gpio_write(5, LOW); // SN74HC4851 A(S0) RPI3 5
        bcm2835_gpio_write(6, LOW); // SN74HC4851 B(S1) RPI3 6 
        bcm2835_gpio_write(13, LOW); // SN74HC4851 C(S2) RPI3 13
    }
    else if(outNum == 1)
    { 
        std::cout << "OUT no.1" << std::endl;
        bcm2835_gpio_write(5, HIGH);
        bcm2835_gpio_write(6, LOW); 
        bcm2835_gpio_write(13, LOW);	
    }
    else if(outNum == 2) 
    {
        std::cout << "OUT no.2" << std::endl;
        bcm2835_gpio_write(5, LOW);
        bcm2835_gpio_write(6, HIGH);
        bcm2835_gpio_write(13, LOW);	 
    }
    else if(outNum == 3) 
    {
        std::cout << "OUT no.3" << std::endl;
        bcm2835_gpio_write(5, HIGH);
        bcm2835_gpio_write(6, HIGH);
        bcm2835_gpio_write(13, LOW);	 
    }
    else if(outNum == 4) 
    {
        std::cout << "OUT no.4" << std::endl;
        bcm2835_gpio_write(5, LOW);
        bcm2835_gpio_write(6, LOW);
        bcm2835_gpio_write(13, HIGH);	 
    }
    else if(outNum == 5) 
    {
        std::cout << "OUT no.5" << std::endl;
        bcm2835_gpio_write(5, HIGH);
        bcm2835_gpio_write(6, LOW);
        bcm2835_gpio_write(13, HIGH);	 
    }
    
    printf("Pulse width set to %d\n", pWidth);
    while(timeout)
    {
         pwmWrite(18, pWidth);
         delay(1000);

         if(timeoutSet)
             timeout--;
    }

    return 0;
}
