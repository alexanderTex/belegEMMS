#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <sstream>

/**
 * @brief The Logger class
 * Logger singleton class
 * use to log errors and info texts
 */
class Logger
{
public:
    virtual ~Logger();

    static Logger *GetLoggerIntance()
    {
        if(Logger::instance == NULL)
        {
            instance = new Logger();
        }
        return Logger::instance;
    }

    /**
     * @brief LogInfo
     * Marks the message by adding "INFO" in the beginning and logs it
     * @param message
     */
    inline void LogInfo(std::string message)
    {
        std::stringstream s;

        s << "INFO : " << message;

        Logger::instance->Log(s.str());
    }

    /**
     * @brief LogError
     * Marks the message by adding "ERROR" in the beginning and logs it
     * @param message
     */
    inline void LogError(std::string message)
    {
        std::stringstream s;

        s << "ERROR : " << message;

        Logger::instance->Log(s.str());
    }

    /**
     * @brief Log
     * Logs the message
     * @param message
     */
    inline virtual void Log(std::string message)
    {
        std::cout << message << std::endl;
    }

private:
    static Logger *instance;

    Logger();

};

#endif // LOGGER_H
