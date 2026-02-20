#pragma once

#include <iostream>
#include <string>

class Logger
{
  public:
    enum class Severity
    {
        Info,
        Warn,
        Error,
        Fatal
    };

  public:
    Logger(const std::string &id) : m_id(id) {}
    Logger(const Logger &other) = delete;
    Logger &operator=(const Logger &other) = delete;

    void log(Severity severity, const std::string &location,
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

        std::cout << '[' << error_message << ']' << " (" << m_id << "::" << location << ") -> "
                  << message << std::endl;
    }

  private:
    const std::string m_id;
};
