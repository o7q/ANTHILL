#pragma once

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
             const std::string &message);

  private:
    const std::string m_id;
};
