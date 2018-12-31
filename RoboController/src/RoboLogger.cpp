//
// Created by Lukas on 10.11.2018.
//

#include "RoboLogger.h"

RoboLogger::RoboLogger()
{
    logging::add_common_attributes();
    logging::register_simple_formatter_factory< log_severity_level, char >("Severity");
    logging::add_file_log
    (
            keywords::file_name = "logrobo.log",
            keywords::auto_flush = true,
            keywords::open_mode = (std::ios::out | std::ios::app),
            keywords::format = "%TimeStamp% [%Uptime%] <%Severity%>: %Message%"
    );
    logging::core::get()->add_global_attribute("Uptime", attrs::timer());
}

RoboLogger* RoboLogger::logger()
{
    static std::unique_ptr<RoboLogger> upr(new RoboLogger());
    return upr.get();
}

void RoboLogger::trivial_log(std::string msg)
{
    std::unique_lock<std::mutex> lk(logMtx);
    BOOST_LOG(lg) << msg;
}

void RoboLogger::severity_log(log_severity_level sl, std::string msg)
{
    std::unique_lock<std::mutex> lk(logMtx);
    BOOST_LOG_SEV(lg, sl) << msg;
}

void RoboLogger::severity_log(log_severity_level sl, std::string fnc_name, std::string msg)
{
    std::unique_lock<std::mutex> lk(logMtx);
    BOOST_LOG_SEV(lg, sl) << "[" + fnc_name + "][Line:"+std::to_string(__LINE__)+"] " << msg;
}

void RoboLogger::timed_log(log_severity_level sl, uint32_t interval_ms, std::string msg)
{
    static auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    std::chrono::duration<double> diff = end-start;
    if(diff.count() > double(interval_ms)/1000)
    {
        std::unique_lock<std::mutex> lk(logMtx);
        BOOST_LOG_SEV(lg, sl) << msg;
        start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    }
}

void RoboLogger::timed_log(log_severity_level sl, uint32_t interval_ms, std::string fnc_name, std::string msg)
{
    static auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    std::chrono::duration<double> diff = end-start;
    if(diff.count() > double(interval_ms)/1000)
    {
        std::unique_lock<std::mutex> lk(logMtx);
        BOOST_LOG_SEV(lg, sl) << "[" + fnc_name + "][Line:"+std::to_string(__LINE__)+"] " << msg;
        start = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    }
}

