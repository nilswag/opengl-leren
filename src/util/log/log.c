#include <stdarg.h>
#include <stdio.h>

#include "log.h"
#include "util/core/defines.h"

void _log(Level level, const char* msg, ...)
{
    if (level < 0 || level >= COUNT) return; // out of bounds

    static const char* prefix[COUNT] = { "", "[INFO]", "[WARN]", "[ERROR]" };

    char buf[1024];
    i32 n = sprintf(buf, "%s %s", prefix[level], msg);
    if (n < 0) return; // formatting error
    
    va_list args;
    va_start(args, msg);
    vprintf(buf, args);
    va_end(args);
}   
