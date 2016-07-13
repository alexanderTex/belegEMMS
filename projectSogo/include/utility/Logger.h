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
        if(instance == NULL)
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
     * @brief LogInfo
     * Marks the message by adding "INFO" in the beginning and logs it
     * @param message
     */
    inline void LogInfo(std::string message, std::string file, int line)
    {
        std::stringstream s;

        s << "INFO : " << message << "\n\n" << "File : " << file << "\n" << "Line : " << line;

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
     * @brief LogError
     * Marks the message by adding "ERROR" in the beginning and logs it
     * @param message
     */
    inline void LogError(std::string message, std::string file, int line)
    {
        std::stringstream s;

        s << "ERROR : " << message << "\n\n" << "File : " << file << "\n" << "Line : " << line;

        Logger::instance->Log(s.str());
    }


private:
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
    Logger(const Logger &src);

};

#endif // LOGGER_H
