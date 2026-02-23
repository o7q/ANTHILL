#include "logger.hpp"

#include <iostream>
#include <string>

void Logger::log(Severity severity, const std::string &location,
                 const std::string &message)
{
    std::string error_message = "";

    switch (severity)
    {
    case Severity::Info:
        error_message = "INFO";
        break;
    case Severity::Warn:
        error_message = "WARNING";
        break;
    case Severity::Error:
        error_message = "ERROR";
        break;
    case Severity::Fatal:
        error_message = "FATAL";
        break;
    }

    std::cout << '[' << error_message << ']' << " (" << m_id << "::" << location
              << ") -> " << message << std::endl;
}
