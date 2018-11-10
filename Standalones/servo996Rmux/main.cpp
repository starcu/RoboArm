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
#include "Servo.h"

std::condition_variable cv;
std::mutex mtx;
int timeout = 1;
bool done = false;
void worker(Multiplexer& mux, bool timeoutSet, int& timeout);
void scheduler();

Servo servo(18);
uint16_t gW = 0;

int main (int argc, char** argv)
{
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

    servo.setWidth(pWidth);
    gW = pWidth;

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

    std::thread t1(worker, std::ref(mux), timeoutSet, std::ref(timeout));
    std::thread t2(scheduler);
     
    t1.join();
    t2.join();
    
    return 0;
}

void worker(Multiplexer& mux, bool timeoutSet, int& timeout)
{
    printf("Worker thread started!\n");
    std::unique_lock<std::mutex> lk(mtx);
    
    while(!done)
    {
        servo.setWidth(gW);
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