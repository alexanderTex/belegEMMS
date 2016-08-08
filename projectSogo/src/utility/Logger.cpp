#include "../../include/utility/Logger.h"

Logger *Logger::instance = NULL;

Logger::Logger(){}

Logger::Logger(const Logger &src){}

Logger::~Logger()
{
    std::cout << "Logger destroyed" << std::endl;
}

/**
 * @brief LogInfo
 * Marks the message by adding "INFO" in the beginning and logs it
 * @param message
 */
void  Logger::LogInfo(std::string message)
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
void  Logger::LogInfo(std::string message, std::string file, int line)
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
void  Logger::LogError(std::string message)
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
void  Logger::LogError(std::string message, std::string file, int line)
{
    std::stringstream s;

    s << "ERROR : " << message << "\n\n" << "File : " << file << "\n" << "Line : " << line;

    Logger::instance->Log(s.str());
}

/**
 * @brief LogPath
 * Display the line and the filepath
 * Example in file:
 *      LOGPATH();
 * @param line
 * @param filepath
 */
void  Logger::LogPath(int line, std::string filepath)
{
    std::stringstream s;

    s << "Line: " << line << " " << "File: " << filepath;

    Logger::instance->Log(s.str());
}


/**
 * @brief LogPath
 * Display the line, filepath and a message
 * Example in file:
 *      LOG("msg");
 * @param line
 * @param filepath
 * @param msg
 */
void  Logger::LogPath(int line, std::string filepath, std::string msg)
{
    std::stringstream s;

    s << "Line: " << line << " File: " << filepath << " >> "  << msg;

    Logger::instance->Log(s.str());
}

void Logger::Log(std::string message)
{
    std::cout << message << std::endl;
}
