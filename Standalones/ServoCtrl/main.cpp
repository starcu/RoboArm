#include <wiringPi.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <mutex>
#include "Servo.h"

std::condition_variable cv;
std::mutex mtx;
int timeout = 1;
bool done = false;
void worker(int pWidth, bool timeoutSet, int& timeout);
void scheduler();

int main (int argc, char** argv)
{
    //PWM
    Servo servo(18);

    uint16_t pWidth = 0; // minimum 0.5444ms
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

    servo.setWidth(4543);

    std::cout << "WIDTH = " << servo.getWidth() << std::endl;

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

    printf("Pulse width set to %d\n", pWidth);

    std::thread t1(worker, pWidth, timeoutSet, std::ref(timeout));
    std::thread t2(scheduler);
     
    t1.join();
    t2.join();
    
    return 0;
}

void worker(int pWidth, bool timeoutSet, int& timeout)
{
    printf("Worker thread started!\n");
    std::unique_lock<std::mutex> lk(mtx);
    
    while(!done)
    {
         pwmWrite(18, pWidth);
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
         //delay(1000);
         
         if(timeoutSet && timeout>0)
         {
             printf("Timeout = %d\n", timeout);
             timeout--;
         }
         else if(timeoutSet)
         {
             printf("Timeout = %d\n", timeout);
             printf("Scheduler informed about job is done...\n");
             lk.unlock();
             cv.notify_all();
             std::this_thread::sleep_for(std::chrono::milliseconds(100)); // stop to be sure scheduler received notification
             lk.lock();
         }
    }
}

void scheduler()
{
    printf("Scheduler thread started!\n");
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []{ return timeout == 0; });
    std::cout << "PWM worker done his work..." << std::endl;
    done = true;
}