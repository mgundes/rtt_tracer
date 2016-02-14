//
// Created by mgundes on 14.02.2016.
//

#include "TimeUtils.h"

long TimeUtils::getSystemTimeInMilliseconds() {
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
