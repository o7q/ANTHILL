#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

namespace Logger
{
inline void log(const std::string &level, const std::string &location,
                const std::string &message)
{
    std::cout << '[' + level + ']' + " (" + location + ") -> " + message
              << std::endl;
}

inline void info(const std::string &location, const std::string &message)
{
    log("INFO", location, message);
}

inline void warn(const std::string &location, const std::string &message)
{
    log("WARN", location, message);
}

inline void error(const std::string &location, const std::string &message)
{
    log("ERROR", location, message);
}

// log and crash program
inline void fatal(const std::string &location, const std::string &message)
{
    log("FATAL", location, message);
    std::abort();
}
}; // namespace Logger
