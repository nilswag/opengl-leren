#include <glad/glad.h>
#include "shader.h"
#include "util/log.h"

static GLuint compile_shader(const char* path, GLenum type)
{
    GLuint id = glCreateShader(type);
    const char* src = read_file(path);

    glShaderSource(id, 1, &src, NULL);
    LOG_INFO("compiling shader with path %s\n", path);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int length = 512;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetShaderInfoLog(id, length, NULL, log);
        LOG_WARN("error during shader compilation with path %s: %s\n", path, log);
    } else LOG_INFO("compiled shader with path %s\n", path);

    return id;
}

GLuint create_shader(const char* vertex_path, const char* fragment_path)
{
    GLuint vertex_shader = compile_shader(vertex_path, GL_VERTEX_SHADER);
    GLuint fragment_shader = compile_shader(fragment_path, GL_FRAGMENT_SHADER);

    GLuint id = glCreateProgram();
    glAttachShader(vertex_shader, GL_VERTEX_SHADER);
    glAttachShader(fragment_shader, GL_FRAGMENT_SHADER);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        int length = 512;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetProgramInfoLog(id, length, NULL, log);
        LOG_WARN("error during shader linking: %s\n", log);
    } else LOG_INFO("linked shader\n");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return id;
}