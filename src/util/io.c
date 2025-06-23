#include "io.h"
#include <stdio.h>
#include <stdlib.h>

char* util_read_file(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "Failed to open file: %s\n", path);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size_t length = ftell(file);
	rewind(file);
	char* buffer = malloc(length + 1);
	if (buffer == NULL)
	{
		fprintf(stderr, "Failed to allocate buffer for file: %s\n", path);
		fclose(file);
		return NULL;
	}

	fread(buffer, sizeof(char), length, file);
	buffer[length] = '\0';
	
	fclose(file);
	return buffer;
}