#include <wiringPi.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "Multiplexer.h"

#define RANGE_MIN 544
#define RANGE_MAX 2400

std::condition_variable cv;
std::mutex mtx;
int timeout = 1;
bool done = false;
void worker(int pWidth, Multiplexer& mux, bool timeoutSet, int& timeout);
void scheduler();

int main (int argc, char** argv)
{
    //PWM
    wiringPiSetupGpio();
    pinMode (18, PWM_OUTPUT) ;
    pwmSetMode (PWM_MODE_MS);
    pwmSetRange (20000);
    pwmSetClock (19.2);

    int pWidth = 0; // minimum 0.5444ms
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
    Multiplexer mux;
    
    mux.setCtrlPins(5,6,13)
    ->addStateToQueue(LOW,LOW,LOW)
    ->addStateToQueue(HIGH,LOW,LOW)
    ->addStateToQueue(LOW,HIGH,LOW)
    ->addStateToQueue(HIGH,HIGH,LOW)
    ->addStateToQueue(LOW,LOW,HIGH)
    ->addStateToQueue(HIGH,LOW,HIGH)
    ->begin();
    
    printf("Pulse width set to %d\n", pWidth);

    std::thread t1(worker, pWidth, std::ref(mux), timeoutSet, std::ref(timeout));
    std::thread t2(scheduler);
     
    t1.join();
    t2.join();
    
    return 0;
}

void worker(int pWidth, Multiplexer& mux, bool timeoutSet, int& timeout)
{
    printf("Worker thread started!\n");
    std::unique_lock<std::mutex> lk(mtx);
    
    while(!done)
    {
         pwmWrite(18, pWidth);
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
         //delay(1000);

         mux.nextState();
         
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
             std::this_thread::sleep_for(std::chrono::milliseconds(100)); // stop to be sure scheduler received cv
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