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

    if (!s.vertex_id || !s.fragment_id)
    {
        fputs("Aborting shader creation due to shader compilation failure.\n", stderr);
        return s;
    }

    glAttachShader(s.id, s.vertex_id);
    glAttachShader(s.id, s.fragment_id);
    glLinkProgram(s.id);

    GLuint success = 1;
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
}

void gfx_shader_set_int(shader_t* shader, const char* name, int value)
{
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1i(location, value);
}

void gfx_shader_set_float(shader_t* shader, const char* name, float value)
{
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1f(location, value);
}

void gfx_shader_set_bool(shader_t* shader, const char* name, int value)
{
    gfx_shader_set_int(shader, name, value);
}


uniform_map_t* gfx_uniform_map_init(void)
{
    uniform_map_t* map = malloc(sizeof(uniform_map_t));
    if (map == NULL)
    {
        fputs("Failed to allocate memory for uniform map.", stderr);
        return NULL;
    }

    map->size = 0;
    map->capacity = 100;
    map->entries = calloc(map->capacity, sizeof(entry_t));

    return map;
}


static void uniform_map_resize(uniform_map_t* map, size_t new_capacity)
{
    if (new_capacity < 1) return;
    entry_t** tmp = calloc(new_capacity, sizeof(entry_t*));
    if (!tmp)
    {
        fputs("Failed to allocate memory to resize uniform map.", stderr);
        return;
    }

    for (int i = 0; i < map->capacity; i++)
    {
        entry_t* current = map->entries[i];
        while (current)
        {
            entry_t* next = current->next;
            unsigned long hash = util_fnv1a_hash(current->key);
            size_t index = hash % new_capacity;
            current->next = tmp[index];
            tmp[index] = current;
            current = next;
        }
    }

    free(map->entries);
    map->entries = tmp;
    map->capacity = new_capacity;
}

void gfx_uniform_map_free(uniform_map_t* map)
{
    free(map->entries);
    free(map);
}

void gfx_uniform_map_put(uniform_map_t* map, const char* key, GLint value)
{
    if ((float)(map->size + 1) / map->capacity > 0.75f) uniform_map_resize(map, map->capacity * 2);
    unsigned long hash = util_fnv1a_hash(key);
    size_t index = hash % map->capacity;

    entry_t* entry = calloc(1, sizeof(entry_t));
    if (entry == NULL)
    {
        fputs("Failed to allocate memory for new map entry.", stderr);
        return;
    }
    entry->key = key;
    entry->value = value;

    entry->next = map->entries[index];
    map->entries[index] = entry;
    map->size++;
}

GLint gfx_uniform_map_get(uniform_map_t* map, const char* key)
{
    if (map->size < 1) return 0;
    unsigned long hash = util_fnv1a_hash(key);
    size_t index = hash % map->capacity;

    entry_t* current = map->entries[index];
    while (current)
    {
        if (strcmp(current->key, key) == 0) return current->value;
        current = current->next;
    }

    return 0;
}

void gfx_uniform_map_remove(uniform_map_t* map, const char* key)
{
    if (map->size < 1)
    {
        fputs("Cannot remove entry from uniform map because it is empty.", stderr);
        return;
    }
    if ((float)map->size / map->capacity < 0.25f) uniform_map_resize(map, map->capacity / 2);

    unsigned long hash = util_fnv1a_hash(key);
    size_t index = hash % map->capacity;

    entry_t* current = map->entries[index];
    entry_t* prev = NULL;
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL) map->entries[index] = current->next;
            else prev->next = current->next;

            free(current);
            map->size--;
            return;
        }

        prev = current;
        current = current->next;
    }
}

void gfx_uniform_map_clear(uniform_map_t* map)
{
    for (int i = 0; i < map->capacity; i++)
        map->entries[i] = NULL;
}
