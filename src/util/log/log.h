#pragma once
#include <stdlib.h>

typedef enum
{
    CLEAR,
    INFO,
    WARNING,
    ERROR,
    COUNT
} Level;

void _log(Level level, const char* msg, ...);

#define LOG(msg, ...) STMT(_log(CLEAR, msg, ##__VA_ARGS__);)
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
