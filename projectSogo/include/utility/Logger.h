#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <sstream>

// replace the first argument by the second
#define LOGPATH() Logger::GetLoggerIntance()->LogPath(__LINE__, __FILE__)
#define LOG(msg) Logger::GetLoggerIntance()->LogPath(__LINE__, __FILE__, msg)


/**
 * @brief The Logger class.
 * Logger singleton class
 * use to log errors and info texts
 *
 * @author Nils Brandt
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
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
    void LogInfo(std::string message);

    /**
     * @brief LogInfo
     * Marks the message by adding "INFO" in the beginning and logs it
     * @param message
     */
    void LogInfo(std::string message, std::string file, int line);

    /**
     * @brief LogError
     * Marks the message by adding "ERROR" in the beginning and logs it
     * @param message
     */
    void LogError(std::string message);

    /**
     * @brief LogError
     * Marks the message by adding "ERROR" in the beginning and logs it
     * @param message
     */
    void LogError(std::string message, std::string file, int line);

    /**
     * @brief LogPath
     * Display the line and the filepath
     * Example in file:
     *      LOGPATH();
     * @param line
     * @param filepath
     */
    void LogPath(int line, std::string filepath);

    /**
     * @brief LogPath
     * Display the line, filepath and a message
     * Example in file:
     *      LOG("msg");
     * @param line
     * @param filepath
     * @param msg
     */
    void LogPath(int line, std::string filepath, std::string msg);

private:
    /**
     * @brief Log
     * Logs the message
     * @param message
     */
    virtual void Log(std::string message);

private:
    static Logger *instance;

    Logger();
    Logger(const Logger &src);

};

#endif // LOGGER_H
