#include "RoboController.h"

Robo::Robo(): initLock(initMtx, std::defer_lock), // enable init lock
              serverThread(&Robo::serverWorker, this), // set workers threads workingpoints
              servoMuxThread(&Robo::servoWorker, this),
              mpuMuxThread(&Robo::mpuWorker, this) {}

void Robo::initialize() // initialize robo structures
{
    initMtx.lock();

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

    initLock.unlock();

    {
        std::unique_lock<std::mutex> lock(initMtx);
        state = RoboState::OK;
    }

    initDoneCV.notify_all(); // notify all workers that strucutres are initialized
}

void Robo::serverWorker()
{
    try
    {
        server.createSocket();
    } 
    catch(...)
    {
        serverWorkerOK = false;
    }

    if(serverWorkerOK)
        RoboLogger::logger()->severity_log(normal, std::string(__func__), "Server (127.0.0.1) worker thread started, server will listen on port 8080");
    else
        RoboLogger::logger()->severity_log(error, std::string(__func__), "Server initialization failed, exiting worker");
        
    //while(serverWorkerOK)
    //{
    try
    {
        server.listenOnSocket(serverWorkerOK);
    } 
    catch(...)
    {
        RoboLogger::logger()->severity_log(warning, std::string(__func__), "Server exception thrown during listening");
    }
    // 

    RoboLogger::logger()->severity_log(normal, std::string(__func__),"SERVER worker done his work");
}

void Robo::servoWorker() 
{
    RoboLogger::logger()->severity_log(normal, std::string(__func__),
                                       "Servo worker thread waiting for initialization to be done");
    {
        std::unique_lock<std::mutex> lk(initMtx);
        initDoneCV.wait(lk, [this] {
            return state == RoboState::OK;
        });
    }

    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Robot init done, Servo worker thread started");
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Settings all servos to base positions");

    while(servoWorkerOK)
    {
        // first functionality is set arm to base figure 90, 90, 135, 45, 90, 60
        for(auto& w: baseFigurePWMWidths)
        {
            servo.setWidth(w);
            servoMux.nextStateWithDelay(SERVO_MUX_SWITCHING_INTERVAL_MS);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SERVO_MUX_WORKER_POLL_INTERVAL_MS));
    }

    RoboLogger::logger()->severity_log(normal, std::string(__func__),"SERVO worker done his work");
}

void Robo::mpuWorker()
{
    RoboLogger::logger()->severity_log(normal, std::string(__func__),
            "MPU worker thread waiting for initialization to be done");

    {
        std::unique_lock<std::mutex> lk(initMtx);
        initDoneCV.wait(lk, [this] {
            return state == RoboState::OK;
        });
    }

    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Robot init done, MPU worker thread started");
    RoboLogger::logger()->severity_log(normal, std::string(__func__), "Initializing all sensors");

    mpuMux.performForEveryState(&MPU::initialize, mpu); // initialize all sensors

    while(mpuWorkerOK)
    {
        // first functionality is just to read data from all accels and gyros pairs
        for(auto& agm: accGyroMagnet)
        {
            mpu.getMeasurements();

            std::get<0>(agm).x = mpu.getAccelX();
            std::get<0>(agm).y = mpu.getAccelY();
            std::get<0>(agm).z = mpu.getAccelZ();

            std::get<1>(agm).x = mpu.getGyroX();
            std::get<1>(agm).y = mpu.getGyroY();
            std::get<1>(agm).z = mpu.getGyroZ();

            //std::get<2>(ag).x = mpu.getMagnetX();
            //std::get<2>(ag).y = mpu.getMagnetY();
            //std::get<2>(ag).z = mpu.getMagnetZ();

            //static uint64_t cnt = 0;
            //std::stringstream msg;
            //msg << "Last MPU[" << cnt%3 << "] positions were: AX:["
            //    << mpu.getAccelX() << "] AY:[" << mpu.getAccelY() << "] AX:[" << mpu.getAccelZ() << "] GX:["
            //    << mpu.getGyroX() << "] GY:[" << mpu.getGyroY() << "] GZ:[" << mpu.getGyroZ() << "]";
            //cnt++;

            //std::cout << msg.str() << std::endl;

            //std::cout << "[ MPU6050 number " + std::to_string(cnt%3) + " ]" << std::endl;
            //std::cout << "\tax=" << std::get<0>(ag).x << "\tay=" << std::get<0>(ag).y << "\taz=" << std::get<0>(ag).z << std::endl;
            //std::cout << "\tgx=" << std::get<1>(ag).x << "\tgy=" << std::get<1>(ag).y << "\tgz=" << std::get<1>(ag).z << std::endl;

            mpuMux.nextState();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(MPU_MUX_WORKER_POLL_INTERVAL_MS));
    }

    RoboLogger::logger()->severity_log(normal, std::string(__func__),"MPU worker done his work");
}
