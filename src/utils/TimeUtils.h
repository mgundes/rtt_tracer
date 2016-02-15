//
// Created by mgundes on 14.02.2016.
//

#ifndef NETWORK_DIAGNOSTICS_UTILS_H
#define NETWORK_DIAGNOSTICS_UTILS_H


#include <chrono>
#include <string>

class TimeUtils {
public:
    static long getSystemTimeInMilliseconds();
    static std::string getLocalTime();
    static std::string getDateAsLogFileName();

};


#endif //NETWORK_DIAGNOSTICS_UTILS_H
