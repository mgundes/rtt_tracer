//
// Created by mgundes on 14.02.2016.
//


#include <fstream>

#ifndef NETWORK_DIAGNOSTICS_LOGGER_H
#define NETWORK_DIAGNOSTICS_LOGGER_H


class Logger {
public:
    enum LOG_LEVEL {
        LOG_LEVEL_CRITICAL = 0,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARNING,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG
    };

    Logger();
    ~Logger();
    static bool init();
    static void deInit();
    static std::ofstream& getStream(const char* funcName, LOG_LEVEL level);
    static std::ofstream& getStream();

private:
    static std::ofstream logFileStream;
};


#define LOG_CRITICAL  Logger().getStream(__FUNCTION__, Logger::LOG_LEVEL_CRITICAL)
#define LOG_ERROR     Logger().getStream(__FUNCTION__, Logger::LOG_LEVEL_ERROR)
#define LOG_WARNING   Logger().getStream(__FUNCTION__, Logger::LOG_LEVEL_WARNING)
#define LOG_INFO      Logger().getStream(__FUNCTION__, Logger::LOG_LEVEL_INFO)
#define LOG_DEBUG     Logger().getStream(__FUNCTION__, Logger::LOG_LEVEL_DEBUG)

#endif //NETWORK_DIAGNOSTICS_LOGGER_H
