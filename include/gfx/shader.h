#pragma once
#include <glad/glad.h>

#include "gfx/map.h"

typedef struct
{
    GLuint id;
    GLuint vertex_id;
    GLuint fragment_id;
    map_t* uniform_map;
} shader_t;

shader_t gfx_shader_init(const char* vertex_src, const char* fragment_src);
void gfx_shader_use(shader_t* shader);
void gfx_shader_free(shader_t* shader);

void gfx_shader_set_int(shader_t* shader, const char* name, int value);
void gfx_shader_set_float(shader_t* shader, const char* name, float value);
void gfx_shader_set_bool(shader_t* shader, const char* name, int value);