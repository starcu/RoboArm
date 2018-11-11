#include "RoboController.h"

Robo::Robo(): initLock(initMtx),
              serverThread(&Robo::serverWorker, this),
              servoMuxThread(&Robo::servoWorker, this),
              mpuMuxThread(&Robo::mpuWorker, this)
{
    initDoneCV.notify_all();
    servoMux
    .setCtrlPins(SERVO_MUX_S0, SERVO_MUX_S1, SERVO_MUX_S2)
    ->addStateToQueue(LOW,LOW,LOW)    // M1Y0
    ->addStateToQueue(HIGH,LOW,LOW)   // M1Y1
    ->addStateToQueue(LOW,HIGH,LOW)   // M1Y2
    ->addStateToQueue(HIGH,HIGH,LOW)  // M1Y3
    ->addStateToQueue(LOW,LOW,HIGH)   // M1Y4
    ->addStateToQueue(HIGH,LOW,HIGH)  // M1Y5
    ->begin();
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Servo multiplexer initialized");

    mpuMux
    .setCtrlPins(MPU_MUX_S0, MPU_MUX_S1, MPU_MUX_S2)
    ->addStateToQueue(LOW,LOW,LOW)   // M0Y0
    ->addStateToQueue(HIGH,LOW,LOW)  // M0Y1
    ->addStateToQueue(LOW,HIGH,LOW)  // M0Y2
    ->begin();
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "MPU multiplexer initialized");

    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Setting Robo state to OK, unlocking initial lock and sending message to workers");
    state = RoboState::OK;
    initLock.unlock();
    initDoneCV.notify_all();
}

void Robo::serverWorker()
{
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Server worker thread started");
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Server (127.0.0.1) will listen on port 8080");

    server.createSocket();
    RoboLogger::logger()->severity_log(normal, std::string(__func__),"Server socket created");

    while(serverWorkerOK)
        server.listenOnSocket();

    RoboLogger::logger()->severity_log(normal, std::string(__func__),"Server socket done his work");
}

void Robo::servoWorker()
{
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Servo worker thread waiting for initialization to be done");
    //std::unique_lock<std::mutex> lk(initMtx);
    //initDoneCV.wait(lk, [this]{ std::cout << "servoWorker notified, state = " + RoboStateToString(state) << std::endl; return state == RoboState::OK;});

    while(RoboState::OK != state)
    {
        std::cout << "servoWorker notified, state = " + RoboStateToString(state) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Init done, Servo worker thread started");

    while(servoWorkerOK)
    {
        // first functionality is set arm to base figure 90, 90, 135, 45, 90, 60
        for(auto& w: baseFigurePWMWidths)
        {
            servo.setWidth(w);
            servoMux.nextState();
        }

        RoboLogger::logger()->timed_log(normal, 10000, std::string(__func__), "All servos set to base position");
        std::this_thread::sleep_for(std::chrono::milliseconds(SERVO_MUX_WORKER_POLL_INTERVAL_MS));
    }
}

void Robo::mpuWorker()
{
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "MPU worker thread waiting for initialization to be done");
    //std::unique_lock<std::mutex> lk(initMtx);
    //initDoneCV.wait(lk, [this]{ std::cout << "mpuWorker notified, state = " + RoboStateToString(state) << std::endl; return state == RoboState::OK;});

    while(RoboState::OK != state)
    {
        std::cout << "mpuWorker notified, state = " + RoboStateToString(state) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Init done, MPU worker thread started");

    uint64_t cnt = 0;
    while(mpuWorkerOK)
    {
        // first functionality is to just read data from all accels and gyros pairs
        for(auto& ag: accGyro)
        {
            mpu.initialize();
            mpu.getMeasurements();

            std::get<0>(ag).x = mpu.getAccelX();
            std::get<0>(ag).y = mpu.getAccelY();
            std::get<0>(ag).z = mpu.getAccelZ();

            std::get<1>(ag).x = mpu.getGyroX();
            std::get<1>(ag).y = mpu.getGyroY();
            std::get<1>(ag).z = mpu.getGyroZ();

            //std::cout << "[ MPU6050 number " + std::to_string(cnt%3) + " ]" << std::endl;
            //std::cout << "\tax=" << std::get<0>(ag).x << "\tay=" << std::get<0>(ag).y << "\taz=" << std::get<0>(ag).z << std::endl;
            //std::cout << "\tgx=" << std::get<1>(ag).x << "\tgy=" << std::get<1>(ag).y << "\tgz=" << std::get<1>(ag).z << std::endl;
            mpuMux.nextState();
            cnt++;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(MPU_MUX_WORKER_POLL_INTERVAL_MS));
    }
}