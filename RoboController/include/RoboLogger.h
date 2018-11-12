//
// Created by Lukas on 10.11.2018.
//

#ifndef ROBOCONTROLLER_ROBOLOGGER_H
#define ROBOCONTROLLER_ROBOLOGGER_H

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes.hpp>
#include <sstream>
#include <mutex>

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

// We define our own severity levels
enum log_severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};

// The operator is used for regular stream formatting
inline std::ostream& operator<< (std::ostream& strm, log_severity_level level)
{
    static const char* strings[] =
    {
        "normal",
        "notification",
        "warning",
        "error",
        "critical"
    };

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}

// Attribute value tag type
struct severity_tag;

// The operator is used when putting the severity level to log
inline logging::formatting_ostream& operator<< (logging::formatting_ostream& strm, logging::to_log_manip< log_severity_level, severity_tag > const& manip)
{
    static const char* strings[] =
    {
        "normal",
        "notification",
        "warning",
        "error",
        "critical"
    };

    log_severity_level level = manip.get();
    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}

class RoboLogger
{
public:
    RoboLogger(const RoboLogger& r) = delete;

    static RoboLogger* logger();

    void trivial_log(std::string msg);
    void severity_log(log_severity_level sl, std::string msg);
    void severity_log(log_severity_level sl, std::string fnc_name, std::string msg);
    void timed_log(log_severity_level sl, uint32_t interval_ms, std::string msg);
    void timed_log(log_severity_level sl, uint32_t interval_ms, std::string fnc_name, std::string msg);

private:
    RoboLogger();

    src::severity_logger_mt<log_severity_level> lg;
    std::mutex logMtx;
};

#endif //ROBOCONTROLLER_ROBOLOGGER_H
