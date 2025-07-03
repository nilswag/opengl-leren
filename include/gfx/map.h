#pragma once
#include <stddef.h>
#include <glad/glad.h>

typedef struct entry
{
    const char* key;
    GLuint value;
    struct entry_t* next;
} Entry;

typedef struct
{
    size_t size;
    size_t capacity;
    Entry** entries;
} Map;

Map* gfx_uniform_map_init(void);
void gfx_uniform_map_free(Map* map);
void gfx_uniform_map_put(Map* map, const char* key, GLuint value);
GLuint gfx_uniform_map_get(Map* map, const char* key);
void gfx_uniform_map_remove(Map* map, const char* key);
void gfx_uniform_map_clear(Map* map);
