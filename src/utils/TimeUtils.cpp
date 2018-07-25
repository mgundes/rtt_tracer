//
// Created by mgundes on 14.02.2016.
//

#include "TimeUtils.h"
#include <sstream>
#include <chrono>
#include <iomanip>


std::string TimeUtils::GetDateStr()
{
    auto now_time_point = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now_time_point);
    std::stringstream ss;
    ss << std::put_time(std::localtime(reinterpret_cast<const time_t*>(&now_time_t)), "%Y%m%d");
    return ss.str();
}

std::string TimeUtils::GetDateStr(long timeStamp)
{
    std::stringstream ss;
    ss << std::put_time(gmtime(&timeStamp), "%Y%m%d");
    return ss.str();
}

std::string TimeUtils::GetTimeStr()
{
    auto now_time_point = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now_time_point);
    std::stringstream ss;
    ss << std::put_time(std::localtime(reinterpret_cast<const time_t*>(&now_time_t)), "%H:%M:%S");
    return ss.str();
}

//TODO: improve performance
std::string TimeUtils::GetTimeStrMilliSeconds()
{
    auto now_time_point = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now_time_point);
    auto sinceEpochDuration = now_time_point.time_since_epoch();
    auto milliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(sinceEpochDuration).count() % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(reinterpret_cast<const time_t*>(&now_time_t)), "%H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << milliSeconds;
    return ss.str();
}


long long TimeUtils::GetCurrentTimeStamp()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

time_t TimeUtils::GetCurrentTimeStampAsUTC()
{
    time_t t;
    time(&t);
    return mktime(gmtime(&t));
}

long long TimeUtils::GetCurrentTimeStampMilliSecond()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}


std::string TimeUtils::getLogFileNameAsDate()
{
    time_t rawTime;
    struct tm * timeinfo;
    time (&rawTime);
    timeinfo = localtime (&rawTime);

    char buffer [80] = {0};
    strftime(buffer,80,"%d%m%Y",timeinfo);

    return std::string(buffer) + ".log";
}