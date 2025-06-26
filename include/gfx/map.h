#pragma once
#include <stddef.h>
#include <glad/glad.h>

typedef struct entry_t
{
    const char* key;
    GLuint value;
    struct entry_t* next;
} entry_t;

typedef struct
{
    size_t size;
    size_t capacity;
    entry_t** entries;
} map_t;

map_t* gfx_uniform_map_init(void);
void gfx_uniform_map_free(map_t* map);
void gfx_uniform_map_put(map_t* map, const char* key, GLuint value);
GLuint gfx_uniform_map_get(map_t* map, const char* key);
void gfx_uniform_map_remove(map_t* map, const char* key);
void gfx_uniform_map_clear(map_t* map);
