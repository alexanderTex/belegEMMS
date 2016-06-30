#include "../../include/utility/Logger.h"

Logger *Logger::instance = NULL;

Logger::Logger()
{

}

Logger::Logger(const Logger &src)
{

}

Logger::~Logger()
{
    std::cout << "Logger destroyed" << std::endl;
}
