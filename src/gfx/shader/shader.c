#include <stdlib.h>
#include <glad/glad.h>

#include "shader.h"
#include "util/core/defines.h"
#include "util/log/log.h"
#include "util/io/file.h"

static u32 compile_shader(const char* path, GLenum type)
{
    u32 id = glCreateShader(type);
    char* src = read_file(path);
    const char* gl_src = src;

    glShaderSource(id, 1, &gl_src, NULL);
    LOG_INFO("compiling shader with path %s\n", path);
    glCompileShader(id);

    free(src);

    i32 success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        i32 length = 512;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetShaderInfoLog(id, length, NULL, log);
        LOG_WARN("error during shader compilation with path %s: %s\n", path, log);
    } else LOG_INFO("compiled shader with path %s\n", path);

    return id;
}

u32 create_shader(const char* vertex_path, const char* fragment_path)
{
    u32 vertex_shader = compile_shader(vertex_path, GL_VERTEX_SHADER);
    u32 fragment_shader = compile_shader(fragment_path, GL_FRAGMENT_SHADER);

    u32 id = glCreateProgram();

    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);

    i32 success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        i32 length = 512;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetProgramInfoLog(id, length, NULL, log);
        LOG_WARN("error during shader linking: %s\n", log);
    } else LOG_INFO("linked shader\n");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return id;
}