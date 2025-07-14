#pragma once
#include "defines.h"

#define UTIL_VECTOR_MIN_CAP 8

typedef struct
{
    u64 size;
    u64 capacity;
    u64 el_size;
    void* data;
} vec_t;

vec_t util_vec_init(u64 el_size);
void util_vec_free(vec_t* vec);
void util_vec_clear(vec_t* vec);

void util_vec_insert(vec_t* vec, u64 index, void* element);
void util_vec_push_back(vec_t* vec, void* element);

void* util_vec_pop_at(vec_t* vec, u64 index);
void* util_vec_pop_back(vec_t* vec);

void* util_vec_get_at(vec_t* vec, u64 index);
void* util_vec_get_back(vec_t* vec);