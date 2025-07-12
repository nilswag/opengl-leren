#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/io.h"


char* util_io_read_file(const char* path)
{
    FILE* f = fopen(path, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file with path: %s.\n", path);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    rewind(f);
    
    char* buffer = calloc(1, length + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate buffer for file with path: %s\n", path);
        return NULL;
    }

    fread(buffer, sizeof(char), length, f);
    buffer[length] = '\0';
    
    fclose(f);
    return buffer;
}