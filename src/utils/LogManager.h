#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include "easylogging++.h"

class LogManager {
public:
    LogManager();
    LogManager(const std::string& logConfigFile);
    bool init();

private:
    void loadDefaultConfig();
    void loadFileConfig();
    std::string m_logConfigFile;
};

#endif