#pragma once
#include <stdlib.h>
#include "util/defines.h"

typedef enum
{
    INFO,
    WARNING,
    ERROR,
    COUNT
} LogLevel;

void _log(LogLevel level, const char* msg, ...);

#define LOG_INFO(msg, ...) STMT(_log(INFO, msg, ##__VA_ARGS__);)
#define LOG_WARN(msg, ...) STMT(_log(WARNING, msg, ##__VA_ARGS__);)
#define LOG_ERROR(msg, ...) STMT(_log(ERROR, msg, ##__VA_ARGS__);)

#define ASSERT(condition, msg, ...) STMT(       \
    if (!(condition))                           \
    {                                           \
        LOG_ERROR(msg, ##__VA_ARGS__);          \
        exit(-1);                               \
    }                                           \
)
