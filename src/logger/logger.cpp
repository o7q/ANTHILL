#include "logger.hpp"

#include <iostream>
#include <SDL3/SDL.h>

void Logger::log(LogLevel logLevel, const std::string &text, bool showSDLError)
{
    std::string error = "";
    switch (logLevel)
    {
    case LogLevel::Info:
        error = "INFO";
        break;
    case LogLevel::Warning:
        error = "WARN";
        break;
    case LogLevel::Error:
        error = "ERROR";
        break;
    case LogLevel::Fatal:
        error = "FATAL";
        break;
    }

    if (showSDLError)
    {
        std::cout << '[' << error << ']' << " " << text << '\n'
                  << SDL_GetError() << std::endl;
        SDL_ClearError();
    }
    else
    {
        std::cout << '[' << error << ']' << " " << text << std::endl;
    }
}