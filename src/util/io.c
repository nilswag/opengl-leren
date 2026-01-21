#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "log.h"

char* read_file(const char* path)
{
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", RESOURCES_PATH, path);

    FILE* file = fopen(full_path, "r");
    // ASSERT(file != NULL, "failed to open file with path %s\n", path);
    if (file == NULL)
    {
        LOG_WARN("failed to open file with path %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buf = (char*)malloc((length + 1) * sizeof(char));

    size_t i = 0;
    char c;
    while ((c = fgetc(file)) != EOF) buf[i++] = c;
    buf[length] = '\0';

    LOG_INFO("read file with path %s\n", path);
    return buf;
}
