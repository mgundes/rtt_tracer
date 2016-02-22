//
// Created by mgundes on 14.02.2016.
//

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
    return (std::ofstream &) (logFileStream << TimeUtils::getLocalTime() << " " << funcName << " [" << LogLevelStr[level] << "] :");
}

std::ofstream& Logger::getStream()
{
    return  logFileStream;
}
