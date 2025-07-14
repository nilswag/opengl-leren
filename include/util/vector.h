#pragma once
#include "defines.h"


#define UTIL_VECTOR_INITIAL_SIZE 100


typedef struct
{
    void* data;
    u64 size;
    u64 capacity;
    u64 element_size;
} vector_t;


vector_t util_vector_init(u64 initial_capacity, u64 element_size);
vector_t util_vector_init(u64 element_size);
void util_vector_free(vector_t* vec);

void util_vector_push(vector_t* vec, void* element);
void util_vector_push_first(vector_t* vec, void* element);
void util_vector_insert(vector_t* vec, u64 index, void* element);