#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum
{
    INFO,
    WARNING,
    ERROR,
    COUNT
} LogLevel;

void _log(LogLevel level, const char* msg, ...)
{
    if (level < 0 || level >= COUNT) return; // out of bounds

    static const char* prefix[COUNT] = { "[INFO]", "[WARN]", "[ERROR]" };

    char buf[1024];
    int n = sprintf(buf, "%s %s", prefix[level], msg);
    if (n < 0) return; // formatting error
    
    va_list args;
    va_start(args, msg);
    vprintf(buf, args);
    va_end(args);
}   

#define LOG_INFO(msg, ...) do { _log(INFO, msg, ##__VA_ARGS__); } while(0)
#define LOG_WARN(msg, ...) do { _log(WARNING, msg, ##__VA_ARGS__); } while(0)
#define LOG_ERROR(msg, ...) do { _log(ERROR, msg, ##__VA_ARGS__); } while(0)

#define ASSERT(condition, msg, ...) do {        \
    if (!condition)                             \
    {                                           \
        LOG_ERROR(msg, ##__VA_ARGS__);          \
        exit(-1);                               \
    }                                           \
} while(0)