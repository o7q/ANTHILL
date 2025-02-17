#pragma once

#include <string>

namespace Log
{
    enum class Level
    {
        Info,
        Warn,
        Error,
        Fatal
    };

    extern bool enabled;
    void log(Level logLevel, const std::string &module, const std::string &text, bool showSDLError = false);
};