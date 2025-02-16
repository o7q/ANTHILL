#include "logger.hpp"

#include <iostream>

#include <SDL3/SDL.h>

namespace Log
{
    bool enabled = true;
};

void Log::log(Type logLevel, const std::string &module, const std::string &text, bool showSDLError)
{
    if (!enabled)
    {
        return;
    }

    std::string error = "";
    switch (logLevel)
    {
    case Type::Info:
        error = "INFO";
        break;
    case Type::Warn:
        error = "WARN";
        break;
    case Type::Error:
        error = "ERROR";
        break;
    case Type::Fatal:
        error = "FATAL";
        break;
    }

    if (showSDLError)
    {
        std::cout << '[' << error << ']' << ' ' << '(' << module << ')' << ' ' << text << '\n'
                  << SDL_GetError() << std::endl;
        SDL_ClearError();
    }
    else
    {
        std::cout << '[' << error << ']' << ' ' << '(' << module << ')' << ' ' << text << std::endl;
    }
}