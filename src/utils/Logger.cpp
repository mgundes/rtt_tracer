//
// Created by mgundes on 14.02.2016.
//

#include <iostream>
#include "Logger.h"
#include "TimeUtils.h"

std::ofstream Logger::logFileStream;
const char* LogLevelStr[] = { "CRITICAL", "ERROR", "WARNING", "CONSOLE", "NORMAL", "DEBUG" };
Logger::Logger()
{

}

Logger::~Logger()
{
    logFileStream << "\n";
    logFileStream.flush();
}

bool Logger::init()
{
    logFileStream.open(TimeUtils::getLogFileNameAsDate(), std::ofstream::out | std::ofstream::app);
    return logFileStream.is_open();
}

void Logger::deInit()
{
    logFileStream.flush();
    logFileStream.close();
}

std::ofstream& Logger::getStream(const char* funcName, LOG_LEVEL level)
{
#ifndef LOG2CONSOLE
    return (std::ofstream &) (logFileStream << TimeUtils::getLocalTime() << " " << funcName << " [" << LogLevelStr[level] << "] :");
#else
    return (std::ofstream &) (std::cout << TimeUtils::getLocalTime() << " " << funcName << " [" << LogLevelStr[level] << "] :");
#endif
}

std::ofstream& Logger::getStream()
{
    return  logFileStream;
}
