#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/io.h"


void util_io_read_file(char* dst, const char* path)
{
    FILE* f = fopen(path, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file with path: %s.\n", path);
        return;
    }

    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
}