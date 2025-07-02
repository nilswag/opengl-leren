    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <string.h>
    #include <glad/glad.h>

    #include "util/util.h"
    #include "gfx/shader.h"


    static GLuint compile_shader(const char* shader_src, GLenum type)
    {
        GLuint id = glCreateShader(type);
        glShaderSource(id, 1, &shader_src, NULL);
        glCompileShader(id);

        GLuint success = 1;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLsizei length = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* log = malloc(length * sizeof(char));
            glGetShaderInfoLog(id, length, NULL, log);
            fprintf(stderr, "Failed to compile shader: \n%s", log);
            free(log);
            glDeleteShader(id);
            return 0;
        }

        return id;
    }


    shader_t gfx_shader_init(const char* vertex_src, const char* fragment_src)
    {
        shader_t s = { 0 };
        s.id = glCreateProgram();
        s.vertex_id = compile_shader(vertex_src, GL_VERTEX_SHADER);
        s.fragment_id = compile_shader(fragment_src, GL_FRAGMENT_SHADER);
        s.uniform_map = gfx_uniform_map_init();

        if (!s.vertex_id || !s.fragment_id)
        {
            fputs("Aborting shader creation due to shader compilation failure.\n", stderr);
            return s;
        }

        glAttachShader(s.id, s.vertex_id);
        glAttachShader(s.id, s.fragment_id);
        glLinkProgram(s.id);

        GLint success = 1;
        glGetProgramiv(s.id, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLsizei length = 0;
            glGetProgramiv(s.id, GL_INFO_LOG_LENGTH, &length);
            char* log = malloc(length * sizeof(char));
            glGetProgramInfoLog(s.id, length, NULL, log);
            fprintf(stderr, "Failed to link shader program: \n%s", log);
            free(log);
        }

        GLint active_uniforms = 0;
        glGetProgramiv(s.id, GL_ACTIVE_UNIFORMS, &active_uniforms);
        GLint uniform_max_length = 0;
        glGetProgramiv(s.id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniform_max_length);
        char* name = malloc(uniform_max_length);
        for (int i = 0; i < active_uniforms; i++)
        {
            GLint size;
            GLenum type;
            glGetActiveUniform(s.id, i, uniform_max_length, NULL, &size, &type, name);
            GLint location = glGetUniformLocation(s.id, name);
            gfx_uniform_map_put(s.uniform_map, name, location);
            // printf("name: %s\n", name);
        }

        return s;
    }


    void gfx_shader_use(shader_t* shader)
    {
        glUseProgram(shader->id);
    }


    void gfx_shader_free(shader_t* shader)
    {
        glDeleteShader(shader->vertex_id);
        glDeleteShader(shader->fragment_id);
        glDeleteProgram(shader->id);
        gfx_uniform_map_free(shader->uniform_map);
    }


    void gfx_shader_set_int(shader_t* shader, const char* name, int value)
    {
        gfx_shader_use(shader);
        glUniform1i(gfx_uniform_map_get(shader->uniform_map, name), value);
    }


    void gfx_shader_set_float(shader_t* shader, const char* name, float value)
    {
        gfx_shader_use(shader);
        glUniform1f(gfx_uniform_map_get(shader->uniform_map, name), value);
    }


    void gfx_shader_set_bool(shader_t* shader, const char* name, int value)
    {
        gfx_shader_set_int(shader, name, value);
    }


    void gfx_shader_set_matrix4fv(shader_t* shader, const char* name, float* value)
    {
        gfx_shader_use(shader);
        glUniformMatrix4fv(gfx_uniform_map_get(shader->uniform_map, name), 1, GL_TRUE, value);
    }
