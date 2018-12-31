#include "RoboController.h"

Robo::Robo(): initLock(initMtx),
              serverThread(&Robo::serverWorker, this),
              i2cMuxThread(&Robo::i2cWorker, this)
{
    i2cMux
    .setCtrlPins(I2C_MUX_S0, I2C_MUX_S1,I2C_BUS::MPU6050)
    ->addStateToQueue(LOW,LOW,LOW,I2C_BUS::MPU6050)    // M1Y0 // mpu0
    ->addStateToQueue(HIGH,LOW,LOW,I2C_BUS::MPU6050)   // M1Y1 // mpu1
    ->addStateToQueue(LOW,HIGH,LOW,I2C_BUS::MPU6050)   // M1Y2 // mpu2
    ->addStateToQueue(HIGH,HIGH,LOW,I2C_BUS::MPU6050)  // M1Y3 // mpu3
    ->addStateToQueue(LOW,LOW,HIGH,I2C_BUS::PCA9685)   // M1Y4 // pca9685
    ->begin();
    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "I2C multiplexer initialized");

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,
            "Setting Robo state to OK, unlocking initial lock and sending message to workers");

    initLock.unlock();

    {
        std::unique_lock<std::mutex> lock(initMtx);
        state = RoboState::OK;
    }

    initDoneCV.notify_all();
}

void Robo::serverWorker()
{
    {
        std::unique_lock<std::mutex> lk(initMtx);
        initDoneCV.wait(lk, [this] {
            return state == RoboState::OK;
        });
    }

    try
    {
        server.createSocket();
        RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,
                "Server (127.0.0.1) worker thread started, server will listen on port 8080");
    }
    catch (std::exception& e)
    {
        RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Server exception thrown with message: " + std::string(e.what()));
    }

    while(serverWorkerOK)
    {
        try
        {
            server.listenOnSocket();
        }
        catch (std::exception& e)
        {
            RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Server exception thrown with message: " + std::string(e.what()));
        }
    }

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,"SERVER worker done his work");
}

/*
void Robo::servoWorker() {
    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,
                                       "Servo worker thread waiting for initialization to be done");
    {
        std::unique_lock<std::mutex> lk(initMtx);
        initDoneCV.wait(lk, [this] {
            return state == RoboState::OK;
        });
    }

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Robot init done, Servo worker thread started");
    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Settings all servos to base positions");

    while(servoWorkerOK)
    {
        // first functionality is set arm to base figure 90, 90, 135, 45, 90, 60
        // no mux necessary for PCA9685

        for(auto& w: baseFigurePWMWidths)
        {
           // std::cout << w << std::endl;
            servo.setWidth(w);
            servoMux.nextStateWithDelay(SERVO_MUX_SWITCHING_INTERVAL_MS);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SERVO_WORKER_POLL_INTERVAL_MS));
    }

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,"SERVO worker done his work");
}

void Robo::mpuWorker()
{
    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,
            "MPU worker thread waiting for initialization to be done");

    {
        std::unique_lock<std::mutex> lk(initMtx);
        initDoneCV.wait(lk, [this] {
            return state == RoboState::OK;
        });
    }

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Robot init done, MPU worker thread started");
    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Initializing all sensors");

    mpuMux.performForEveryState(&MPU::initialize, mpu); // initialize all sensors

    while(mpuWorkerOK)
    {
        // first functionality is just to read data from all accels and gyros pairs
        for(auto& ag: accGyro)
        {
            mpu.getMeasurements();

            std::get<0>(ag).x = mpu.getAccelX();
            std::get<0>(ag).y = mpu.getAccelY();
            std::get<0>(ag).z = mpu.getAccelZ();

            std::get<1>(ag).x = mpu.getGyroX();
            std::get<1>(ag).y = mpu.getGyroY();
            std::get<1>(ag).z = mpu.getGyroZ();

            static uint64_t cnt = 0;
            std::stringstream msg;
            msg << "Last MPU[" << cnt%3 << "] positions were: AX:["
                << mpu.getAccelX() << "] AY:[" << mpu.getAccelY() << "] AX:[" << mpu.getAccelZ() << "] GX:["
                << mpu.getGyroX() << "] GY:[" << mpu.getGyroY() << "] GZ:[" << mpu.getGyroZ() << "]";
            cnt++;

            //std::cout << msg.str() << std::endl;

            //std::cout << "[ MPU6050 number " + std::to_string(cnt%3) + " ]" << std::endl;
            //std::cout << "\tax=" << std::get<0>(ag).x << "\tay=" << std::get<0>(ag).y << "\taz=" << std::get<0>(ag).z << std::endl;
            //std::cout << "\tgx=" << std::get<1>(ag).x << "\tgy=" << std::get<1>(ag).y << "\tgz=" << std::get<1>(ag).z << std::endl;

            mpuMux.nextState();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(MPU_WORKER_POLL_INTERVAL_MS));
    }

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,"MPU worker done his work");
}
*/

void Robo::i2cWorker()
{
    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME,
                                       "I2C worker thread waiting for initialization to be done");

    {
        std::unique_lock<std::mutex> lk(initMtx);
        initDoneCV.wait(lk, [this] {
            return state == RoboState::OK;
        });
    }

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Robot init done, I2C worker thread started");
    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "Initializing all sensors");

    i2cMux.performForEveryStateInBus(I2C_BUS::MPU6050, &MPU::initialize, mpu); // initialize all MPU6050 sensors

    while(i2cWorkerOK)
    {
        /*
         * 1. read data from MPUs
         * 2. control servo channels through PCA9685 servo driver
         */
        auto state = i2cMux.getCurrentState();
        std::cout << "STATE = " << state << std::endl;

        switch(state.getStateBus()) // check of witch bus this state is placed
        {
            case (I2C_BUS::MPU6050):
            {
                std::cout << "MPU_I2C_BUS" << std::endl;
                mpu.getMeasurements();
                static uint64_t cnt = 0;
                std::stringstream msg;
                msg << "Last MPU[" << cnt % 3 << "]";// positions were: AX:["
                   // << mpu.getAccelX() << "] AY:[" << mpu.getAccelY() << "] AX:[" << mpu.getAccelZ() << "] GX:["
                   // << mpu.getGyroX() << "] GY:[" << mpu.getGyroY() << "] GZ:[" << mpu.getGyroZ() << "]";
                cnt++;
                std::cout << msg.str() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                break;
            }

            case (I2C_BUS::PCA9685):
            {
                std::cout << "PCA9685_I2C_BUS" << std::endl;
                uint64_t pcnt = 0;
                for(auto& pwm: baseFigurePWMWidths)
                {
                    // set all 6 channels widths
                    std::cout << "PWM_" << pcnt++ << " = " << pwm << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
            }

            default:
                break;
        }

        i2cMux.nextState(); // go to another device

        std::this_thread::sleep_for(std::chrono::milliseconds(I2C_WORKER_POLL_INTERVAL_MS));
    }

    RoboLogger::logger()->severity_log(normal, FUNCTION_NAME, "I2C worker done his work");
}