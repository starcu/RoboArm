//
// Created by Lukas on 10.11.2018.
//

#ifndef ROBOCONTROLLER_ROBOCONTROLLER_H
#define ROBOCONTROLLER_ROBOCONTROLLER_H

#include "RoboControllerCommon.h"

class Robo
{
public:
    Robo(const Robo& r) = delete;

    void initialize();

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
        servoMuxThread.join();
        mpuMuxThread.join();
    }

private:
    Robo();

   // void initialize();

    void serverWorker();
    void servoWorker();
    void mpuWorker();

    std::thread serverThread;
    std::thread servoMuxThread;
    std::thread mpuMuxThread;

    std::atomic_bool serverWorkerOK{true};
    std::atomic_bool servoWorkerOK{true};
    std::atomic_bool mpuWorkerOK{true};

    SimpleSocketServer server{8080, "127.0.0.1"};

    std::condition_variable initDoneCV;
    std::mutex  initMtx;
    std::unique_lock<std::mutex> initLock;

    RoboState   state{RoboState::UNINITIALIZED};

    MPU         mpu;
    Servo       servo{SERVO_PIN};

    Multiplexer servoMux;
    Multiplexer mpuMux;

    //base positions for all servos
    std::vector<uint16_t> baseFigurePWMWidths {1472, 1472, 1936, 1008, 1472, 1200};

    // accelerometers, gyros and magnetometers common data structure
    std::vector<std::tuple<accel, gyro, magnet>> accGyroMagnet 
    {
        std::make_tuple(accel(), gyro(), magnet()),
        std::make_tuple(accel(), gyro(), magnet()),
        std::make_tuple(accel(), gyro(), magnet()),
        std::make_tuple(accel(), gyro(), magnet())
    };
};

#endif //ROBOCONTROLLER_ROBOCONTROLLER_H
