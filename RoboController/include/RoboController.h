//
// Created by Lukas on 10.11.2018.
//

#ifndef ROBOCONTROLLER_ROBOCONTROLLER_H
#define ROBOCONTROLLER_ROBOCONTROLLER_H

#ifndef BCM2835_NO_DELAY_COMPATIBILITY
    #define BCM2835_NO_DELAY_COMPATIBILITY
#endif

#include <thread>
#include <atomic>
#include "server.h"
#include "Multiplexer.h"
#include "Servo.h"
#include "MPU6050Class.h"
#include "RoboLogger.h"
#include "KalmanFilter.h"

#define SERVO_PIN 18
#define SERVO_MUX_S0 5
#define SERVO_MUX_S1 6
#define SERVO_MUX_S2 13
#define SERVO_MUX_WORKER_POLL_INTERVAL_MS 10
#define SERVO_MUX_SWITCHING_INTERVAL_MS 120

#define MPU_MUX_S0 17
#define MPU_MUX_S1 27
#define MPU_MUX_S2 22
#define MPU_MUX_WORKER_POLL_INTERVAL_MS 20

struct servoLimits
{
    uint16_t min;
    uint16_t max;
    uint16_t base;
};

enum class RoboState
{
    UNINITIALIZED,
    OK,
    WARNING,
    ERROR
};

inline std::string RoboStateToString(RoboState s)
{
    switch(s)
    {
        case RoboState::UNINITIALIZED:
            return "UNINITIALIZED";
        case RoboState::OK:
            return "OK";
        case RoboState::WARNING:
            return "WARNING";
        case RoboState::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

struct accel
{
    int16_t x=0;
    int16_t y=0;
    int16_t z=0;
};

struct gyro
{
    int16_t x=0;
    int16_t y=0;
    int16_t z=0;
};

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
        servoMuxThread.join();
        mpuMuxThread.join();
    }

private:
    Robo();

    SimpleSocketServer server{8080, "127.0.0.1"};

    std::condition_variable initDoneCV;
    std::mutex  initMtx;
    std::unique_lock<std::mutex> initLock;

    RoboState   state;

    MPU          mpu;
    KalmanFilter mpuFilter;
    Servo        servo{SERVO_PIN};

    Multiplexer servoMux;
    Multiplexer mpuMux;

    std::thread serverThread;
    std::thread servoMuxThread;
    std::thread mpuMuxThread;

    std::atomic_bool serverWorkerOK{true};
    std::atomic_bool servoWorkerOK{true};
    std::atomic_bool mpuWorkerOK{true};

    void serverWorker();
    void servoWorker();
    void mpuWorker();

    //base positions for all servos
    std::vector<uint16_t> baseFigurePWMWidths {1472, 1472, 1936, 1008, 1472, 1200};

    // servo limits widths
    std::vector<servoLimits> servosLimits
    {
        /*0*/servoLimits{544, 2400, 1472},
        /*1*/servoLimits{1008, 2400, 1472},
        /*2*/servoLimits{1008, 2400, 1936},
        /*3*/servoLimits{544, 2400, 1008},
        /*4*/servoLimits{544, 2400, 1472},
        /*5*/servoLimits{1100, 1550, 1200}
    };

    // accelerometers and gyros
    std::vector<std::pair<accel, gyro>> accGyro {std::make_pair(accel(), gyro()),
                                                 std::make_pair(accel(), gyro()),
                                                 std::make_pair(accel(), gyro())};
};

#endif //ROBOCONTROLLER_ROBOCONTROLLER_H