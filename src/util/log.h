#pragma once
#include <stdio.h>

enum LogLevel
{
    INFO,
    WARNING,
    ERROR,
    COUNT
};

template<typename... Args>
void _log(LogLevel level, const char* msg, Args... args)
{
    if (level < 0 || level >= LogLevel::COUNT) return; // out of bounds

    static const char* prefix[LogLevel::COUNT] = { "[INFO]", "[WARN]", "[ERRO]" };

    char buf[1024];
    int n = sprintf_s(buf, "%s %s", prefix[level], msg);
    if (n < 0) return; // formatting error
    
    printf(buf, args...);
}

#define LOG_INFO(msg, ...) do { _log(LogLevel::INFO, msg, ##__VA_ARGS__); } while(false)
#define LOG_WARN(msg, ...) do { _log(LogLevel::WARNING, msg, ##__VA_ARGS__); } while(false)
#define LOG_ERROR(msg, ...) do { _log(LogLevel::ERROR, msg, ##__VA_ARGS__); } while(false)