//
// Created by Lukas on 10.11.2018.
//

#ifndef ROBOCONTROLLER_ROBOCONTROLLER_H
#define ROBOCONTROLLER_ROBOCONTROLLER_H

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "server.h"
#include "Multiplexer.h"
//#include "Servo.h" // deprecated -> replaced with PCA9685
#include "MPU6050Class.h"
#include "RoboLogger.h"
#include "RoboControllerCommon.h"

using namespace RoboI2CBuses;

class Robo
{
public:
    Robo(const Robo& r) = delete;

    static Robo* get()
    {
        static std::unique_ptr<Robo> r(new Robo());
        return r.get();
    }

    RoboState getCurrentState() const
    {
        return state;
    }

    ~Robo()
    {
        serverThread.join();
        i2cMuxThread.join();
    }

private:
    Robo();

    SimpleSocketServer server{8080, "127.0.0.1"};

    std::condition_variable initDoneCV;
    std::mutex  initMtx;
    std::unique_lock<std::mutex> initLock;

    RoboState   state;

    MPU         mpu;
    //Servo       servo{SERVO_PIN}; // deprecated -> changed to PCA9685

    Multiplexer i2cMux;

    std::thread serverThread;
    std::thread i2cMuxThread;

    std::atomic_bool serverWorkerOK{true};
    std::atomic_bool i2cWorkerOK{true};

    void serverWorker();
    void i2cWorker();

    //base positions for all servos
    std::vector<uint16_t> baseFigurePWMWidths {1472, 1472, 1936, 1008, 1472, 1200};
};

#endif //ROBOCONTROLLER_ROBOCONTROLLER_H