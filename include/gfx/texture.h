#pragma once
#include <glad/glad.h>

typedef struct
{
    GLuint id;
    GLenum type;
} texture_t;

texture_t gfx_texture_from_file(const char* path, GLenum type, GLenum format);
void gfx_texture_bind(const char* texture, GLint unit);