//
// Created by mgundes on 14.02.2016.
//

#ifndef NETWORK_DIAGNOSTICS_UTILS_H
#define NETWORK_DIAGNOSTICS_UTILS_H

#include <ctime>
#include <chrono>
#include <string>

class TimeUtils {
public:
    static std::string GetDateStr();
    static std::string GetDateStr(long timeStamp);
    static std::string GetTimeStr();
    static std::string GetTimeStrMilliSeconds();
    static long long GetCurrentTimeStamp();
    static time_t GetCurrentTimeStampAsUTC();
    static long long GetCurrentTimeStampMilliSecond();
    static std::string getLogFileNameAsDate();

};


#endif //NETWORK_DIAGNOSTICS_UTILS_H
