#include "../../include/utility/Logger.h"

Logger *Logger::instance = NULL;

Logger::Logger()
{

}
Logger::~Logger()
{
    std::cout << "Logger destroyed" << std::endl;
}
