#pragma once
#include <glad/glad.h>

#include "gfx/map.h"
#include "math/matrix.h"

typedef struct
{
    GLuint id;
    GLuint vertex_id;
    GLuint fragment_id;
    Map* uniform_map;
} Shader;

Shader gfx_shader_init(const char* vertex_src, const char* fragment_src);
void gfx_shader_use(Shader* shader);
void gfx_shader_free(Shader* shader);

void gfx_shader_set_int(Shader* shader, const char* name, int value);
void gfx_shader_set_float(Shader* shader, const char* name, float value);
void gfx_shader_set_bool(Shader* shader, const char* name, int value);
void gfx_shader_set_matrix4fv(Shader* shader, const char* name, Matf4x4* value);