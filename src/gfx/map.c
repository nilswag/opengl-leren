#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/util.h"
#include "gfx/map.h"


static void uniform_map_resize(map_t* map, size_t new_capacity)
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
            unsigned long long hash = util_fnv1a_hash(current->key);
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


map_t* gfx_uniform_map_init(void)
{
    map_t* map = malloc(sizeof(map_t));
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


void gfx_uniform_map_free(map_t* map)
{
    free(map->entries);
    free(map);
}


void gfx_uniform_map_put(map_t* map, const char* key, GLuint value)
{
    if ((float)(map->size + 1) / map->capacity > 0.75f) uniform_map_resize(map, map->capacity * 2);
    unsigned long long hash = util_fnv1a_hash(key);
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


GLuint gfx_uniform_map_get(map_t* map, const char* key)
{
    if (map->size < 1) return -1;
    unsigned long long hash = util_fnv1a_hash(key);
    size_t index = hash % map->capacity;

    entry_t* current = map->entries[index];
    while (current)
    {
        if (strcmp(current->key, key) == 0) return current->value;
        current = current->next;
    }

    return 0;
}


void gfx_uniform_map_remove(map_t* map, const char* key)
{
    if (map->size < 1)
    {
        fputs("Cannot remove entry from uniform map because it is empty.", stderr);
        return;
    }
    if ((float)map->size / map->capacity < 0.25f) uniform_map_resize(map, map->capacity / 2);

    unsigned long long hash = util_fnv1a_hash(key);
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


void gfx_uniform_map_clear(map_t* map)
{
    for (int i = 0; i < map->capacity; i++)
        map->entries[i] = NULL;
}
