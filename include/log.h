#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

#ifdef _DEBUG

#define LOG(format, ...) do {                                        \
    fprintf(stdout, format, ##__VA_ARGS__);                          \
    fprintf(stdout, "\n");                                           \
} while (false)

#define LOG_ERROR(format, ...) do {                                  \
    fprintf(stderr, "%s:%d Error: ", __FILENAME__, __LINE__);        \
    fprintf(stderr, format, ##__VA_ARGS__);                          \
    fprintf(stderr, "\n");                                           \
} while (false)

#define LOG_FATAL(format, ...) do {                                 \
    fprintf(stderr, "%s:%d Fatal: ", __FILENAME__, __LINE__);       \
    fprintf(stderr, format, ##__VA_ARGS__);                         \
    fprintf(stderr, "\n");                                          \
    exit(-1);                                                       \
} while (false)

#else

#define LOG_HELPER(stream, format, ...)
#define LOG(format, ...)
#define LOG_ERROR(format, ...)
#define LOG_FATAL(format, ...)

#endif