/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file logger.hpp
 * @version 1.0
 * @date 08/03/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "platform.hpp"

#include <iostream>
#include <sstream>


enum LogLevel {
    logERROR = 0,
    logWARNING,
    logDEBUG,
};

class Logger
{
public:
    Logger(LogLevel logLevel = logERROR);

    template <typename T>
    Logger & operator<<(T const & value)
    {
        buffer_ << value;
        return *this;
    }

    static void Clear(LogLevel logLevel);
    static std::string Log(LogLevel logLevel);
    ~Logger();

private:
    LogLevel level_;
    std::ostringstream buffer_;
    static std::stringstream persistent_logs_[3];
};

extern LogLevel loglevel;

#define log(level) \
if (level > loglevel) ; \
else Logger(level)

