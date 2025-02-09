#pragma once

#include <string>

namespace Log
{
    enum class Type
    {
        Info,
        Warn,
        Error,
        Fatal
    };

    void log(Type logLevel, const std::string &module, const std::string &text, bool showSDLError = false);
};