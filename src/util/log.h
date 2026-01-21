#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    INFO,
    WARNING,
    ERROR,
    COUNT
} LogLevel;

void _log(LogLevel level, const char* msg, ...);

#define LOG_INFO(msg, ...) do { _log(INFO, msg, ##__VA_ARGS__); } while(false)
#define LOG_WARN(msg, ...) do { _log(WARNING, msg, ##__VA_ARGS__); } while(false)
#define LOG_ERROR(msg, ...) do { _log(ERROR, msg, ##__VA_ARGS__); } while(false)

#define ASSERT(condition, msg, ...) do {        \
    if (!(condition))                           \
    {                                           \
        LOG_ERROR(msg, ##__VA_ARGS__);          \
        exit(-1);                               \
    }                                           \
} while(false)
