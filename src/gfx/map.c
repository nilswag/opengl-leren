#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/util.h"
#include "gfx/map.h"


static void uniform_map_resize(Map* map, size_t new_capacity)
{
    if (new_capacity < 1) return;
    Entry** tmp = calloc(new_capacity, sizeof(Entry*));
    if (!tmp)
    {
        fputs("Failed to allocate memory to resize uniform map.", stderr);
        return;
    }

    for (int i = 0; i < map->capacity; i++)
    {
        Entry* current = map->entries[i];
        while (current)
        {
            Entry* next = current->next;
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


Map* gfx_uniform_map_init(void)
{
    Map* map = malloc(sizeof(Map));
    if (map == NULL)
    {
        fputs("Failed to allocate memory for uniform map.", stderr);
        return NULL;
    }

    map->size = 0;
    map->capacity = 100;
    map->entries = calloc(map->capacity, sizeof(Entry*));

    return map;
}


void gfx_uniform_map_free(Map* map)
{
    free(map->entries);
    free(map);
}


void gfx_uniform_map_put(Map* map, const char* key, GLuint value)
{
    if ((float)(map->size + 1) / map->capacity > 0.75f) uniform_map_resize(map, map->capacity * 2);
    unsigned long long hash = util_fnv1a_hash(key);
    size_t index = hash % map->capacity;

    Entry* entry = calloc(1, sizeof(Entry));
    if (entry == NULL)
    {
        fputs("Failed to allocate memory for new map entry.", stderr);
        return;
    }
    entry->key = _strdup(key);
    entry->value = value;

    entry->next = map->entries[index];
    map->entries[index] = entry;
    map->size++;
}


GLuint gfx_uniform_map_get(Map* map, const char* key)
{
    if (map->size < 1) return 0;
    unsigned long long hash = util_fnv1a_hash(key);
    size_t index = hash % map->capacity;

    Entry* current = map->entries[index];    
    while (current)
    {
        if (strcmp(current->key, key) == 0) return current->value;
        current = current->next;
    }

    return 0;
}


void gfx_uniform_map_remove(Map* map, const char* key)
{
    if (map->size < 1)
    {
        fputs("Cannot remove entry from uniform map because it is empty.", stderr);
        return;
    }
    if ((float)map->size / map->capacity < 0.25f) uniform_map_resize(map, map->capacity / 2);

    unsigned long long hash = util_fnv1a_hash(key);
    size_t index = hash % map->capacity;

    Entry* current = map->entries[index];
    Entry* prev = NULL;
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


void gfx_uniform_map_clear(Map* map)
{
    for (int i = 0; i < map->capacity; i++)
        map->entries[i] = NULL;
}
