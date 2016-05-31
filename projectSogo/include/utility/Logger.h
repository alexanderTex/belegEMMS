#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <sstream>

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

    inline void LogInfo(std::string message)
    {
        std::stringstream s;

        s << "INFO : " << message;

        Logger::instance->Log(s.str());
    }

    inline void LogError(std::string message)
    {
        std::stringstream s;

        s << "ERROR : " << message;

        Logger::instance->Log(s.str());
    }

    inline virtual void Log(std::string message)
    {
        std::cout << message << std::endl;
    }

private:
    static Logger *instance;

    Logger();

};

#endif // LOGGER_H
