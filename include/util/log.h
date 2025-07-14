#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

#ifdef _DEBUG

#define LOG_HELPER(stream, format, ...) fprintf(stream, format, __VA_ARGS__)

#define LOG(format, ...) do {                                       \
    LOG_HELPER(stdout, format, __VA_ARGS__);                        \
    LOG_HELPER(stdout, "\n");                                       \
} while (false)

#define LOG_ERROR(format, ...) do {                                 \
    LOG_HELPER(stderr, "%s:%d Error: ", __FILENAME__, __LINE__);    \
    LOG_HELPER(stderr, format, __VA_ARGS__);                        \
    LOG_HELPER(stderr, "\n");                                       \
} while (false)

#define LOG_RETURN(format, ...) do {                                \
    LOG_ERROR(format, __VA_ARGS__);                                 \
    return;                                                         \
} while (false)

#define LOG_RETURN_VAL(ret, format, ...) do {                       \
    LOG_ERROR(format, __VA_ARGS__);                                 \
    return ret;                                                     \
} while (false)

#define LOG_FATAL(format, ...) do {                                 \
    LOG_HELPER(stderr, "%s:%d Fatal: ", __FILENAME__, __LINE__);    \
    LOG_HELPER(stderr, format, __VA_ARGS__);                        \
    LOG_HELPER(stderr, "\n");                                       \
    exit(-1);                                                       \
} while (false)

#else

#define LOG_HELPER(stream, format, ...)
#define LOG(format, ...)
#define LOG_RETURN(format, ret, ...)
#define LOG_ERROR(format, ...)
#define LOG_FATAL(format, ...)

#endif