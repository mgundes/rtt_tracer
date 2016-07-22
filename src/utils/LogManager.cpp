#include "LogManager.h"
#include "Utils.h"

INITIALIZE_EASYLOGGINGPP

const std::string DefaultConfigText = "* GLOBAL: \n \
                                         TO_FILE = true \n \
                                         FILENAME = \"info.%datetime{%Y%M%d}.log\" \n \
                                         TO_STANDARD_OUTPUT   =  false \n \
                                         * WARNING: \n \
                                         TO_STANDARD_OUTPUT   =  true \n \
                                         * ERROR: \n \
                                         TO_STANDARD_OUTPUT   =  true \n \
                                         * FATAL: \n \
                                         TO_STANDARD_OUTPUT   =  true";


LogManager::LogManager() : m_logConfigFile("")
{
}

LogManager::LogManager(const std::string& logConfigFile) : m_logConfigFile(logConfigFile)
{
}

bool LogManager::init()
{
    try {
        if (m_logConfigFile.empty() || !Utils::fileExists(m_logConfigFile)) {
            loadDefaultConfig();
        } else {
            loadFileConfig();
        }
        return true;
    } catch (...) {
        return false;
    }
}

void LogManager::loadDefaultConfig()
{
    el::Configurations conf;
    conf.setToDefault();
    conf.parseFromText(DefaultConfigText);
    
    el::Loggers::reconfigureAllLoggers(conf);
}

void LogManager::loadFileConfig()
{
    el::Configurations conf;
    conf.setToDefault();
    conf.parseFromFile(m_logConfigFile);
    
    el::Loggers::reconfigureAllLoggers(conf);
}