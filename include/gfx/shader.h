#pragma once
#include <glad/glad.h>

typedef struct
{
    GLuint id;
    GLuint vertex_id;
    GLuint fragment_id;
} shader_t;

shader_t gfx_shader_init(const char* vertex_src, const char* fragment_src);
void gfx_shader_use(shader_t* shader);
void gfx_shader_free(shader_t* shader);

void gfx_shader_set_int(shader_t* shader, const char* name, int value);
void gfx_shader_set_float(shader_t* shader, const char* name, float value);
void gfx_shader_set_bool(shader_t* shader, const char* name, int value);


typedef struct entry_t
{
    const char* key;
    GLint value;
    struct entry_t* next;
} entry_t;

typedef struct
{
    size_t size;
    size_t capacity;
    entry_t** entries;
} uniform_map_t;

uniform_map_t* gfx_uniform_map_init(void);
void gfx_uniform_map_free(uniform_map_t* map);
void gfx_uniform_map_put(uniform_map_t* map, const char* key, GLint value);
GLint gfx_uniform_map_get(uniform_map_t* map, const char* key);
void gfx_uniform_map_remove(uniform_map_t* map, const char* key);
void gfx_uniform_map_clear(uniform_map_t* map);
