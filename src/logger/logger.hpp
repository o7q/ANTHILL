#pragma once

#include <string>

namespace Logger
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error,
        Fatal
    };

    void log(LogLevel logLevel, const std::string &text, bool showSDLError = false);
};