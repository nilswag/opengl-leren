#include <stdlib.h>
#include <string.h>
#include "util/vector.h"
#include <defines.h>
#include <log.h>

vec_t util_vec_init(u64 el_size)
{
    vec_t v = { 0 };
    v.size = 0;
    v.capacity = UTIL_VECTOR_MIN_CAP;
    v.el_size = el_size;
    v.data = malloc(v.el_size * v.capacity);
    if (!v.data) LOG_FATAL("Unable to allocate memory for vector.");

    return v;
}

void util_vec_free(vec_t* vec)
{
    vec->size = 0;
    vec->capacity = UTIL_VECTOR_MIN_CAP;
    vec->el_size = 0;
    free(vec->data);
    vec->data = NULL;
}

void util_vec_clear(vec_t* vec)
{
    for (u64 i = 0; i < vec->size; i++)
    {
        void* dest = (u8*)vec->data + i * vec->el_size;
        memset(dest, 0, vec->el_size);
    }
}

static void _resize_vec(vec_t* vec, u64 new_cap)
{
    void* new = realloc(vec->data, vec->el_size * new_cap);
    if (!new) LOG_FATAL("Unable to allocate memory for vector.");
    vec->data = new;
    vec->capacity = new_cap;
}

static void _ensure_capacity(vec_t* vec)
{
    if (vec->size >= vec->capacity)
        _resize_vec(vec, vec->capacity * 2);
    else if ((f32)vec->size / vec->capacity < 0.25f && vec->capacity > UTIL_VECTOR_MIN_CAP)
        _resize_vec(vec, MAX(vec->capacity / 2, 1));
}

void util_vec_insert(vec_t* vec, u64 index, void* element)
{
    if (index > vec->size) LOG_FATAL("Index out of bounds for %llu.", index);
    _ensure_capacity(vec);

    u64 to_move = vec->size - index;
    if (to_move > 0)
    {
        void* dest = (u8*)vec->data + (index + 1) * vec->el_size;
        void* src = (u8*)vec->data + index * vec->el_size;
        memmove(dest, src, to_move * vec->el_size);
    }
    void* dest = (u8*)vec->data + index * vec->el_size;
    memcpy(dest, element, vec->el_size);

    vec->size++;
}

void util_vec_push_back(vec_t* vec, void* element)
{
    util_vec_insert(vec, vec->size, element);
}

void* util_vec_pop_at(vec_t* vec, u64 index)
{
    if (vec->size < 1) LOG_FATAL("Unable to pop from vector since it is empty.");
    if (index >= vec->size) LOG_FATAL("Index out of bounds for %llu.", index);

    void* src = (u8*)vec->data + index * vec->el_size;
    void* ret = malloc(vec->el_size);
    if (!ret) LOG_FATAL("Unable to allocate memory for vector.");
    memcpy(ret, src, vec->el_size);

    u64 to_move = vec->size - index - 1;
    if (to_move > 0)
    {
        void* dest = (u8*)vec->data + index * vec->el_size;
        void* src = (u8*)vec->data + (index + 1) * vec->el_size;
        memmove(dest, src, to_move * vec->el_size);
    }

    vec->size--;
    _ensure_capacity(vec);
    
    return ret;
}

void* util_vec_pop_back(vec_t* vec)
{
    return util_vec_pop_at(vec, vec->size - 1);
}

void* util_vec_get_at(vec_t* vec, u64 index)
{
    if (vec->size < 1) LOG_FATAL("Unable to pop from vector since it is empty.");
    if (index >= vec->size) LOG_FATAL("Index out of bounds for %llu.", index);
    return (u8*)vec->data + index * vec->el_size;
}

void* util_vec_get_back(vec_t* vec)
{
    return util_vec_get_at(vec, vec->size - 1);
}