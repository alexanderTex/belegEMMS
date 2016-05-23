#include "../../include/utility/Logger.h"

Logger *Logger::instance = NULL;

Logger::Logger()
{

}
Logger::~Logger()
{
    delete(Logger::GetLoggerIntance());
}
