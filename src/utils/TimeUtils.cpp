//
// Created by mgundes on 14.02.2016.
//

#include "TimeUtils.h"
#include <ctime>

long TimeUtils::getSystemTimeInMilliseconds()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

std::string TimeUtils::getLocalTime()
{
    time_t rawTime;
    struct tm * timeinfo;
    time (&rawTime);
    timeinfo = localtime (&rawTime);

    char buffer [80] = {0};
    strftime(buffer,80,"%F %T ",timeinfo);

    return std::string(buffer);
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