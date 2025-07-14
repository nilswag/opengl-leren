#include <stdlib.h>

#include "defines.h"
#include "util/log.h"
#include "util/vector.h"


vector_t util_vector_init(u64 capacity, u64 element_size)
{
    vector_t self = { 0 };
    self.capacity = capacity;
    self.element_size = element_size;
    self.data = calloc(capacity, element_size);
    if (!self.data) LOG_RETURN("Failed to allocate memory for vector data.");
    return self;
}


vector_t util_vector_init(u64 element_size)
{
    vector_t self = { 0 };
    self.capacity = UTIL_VECTOR_INITIAL_SIZE;
    self.element_size = element_size;
    self.data = calloc(UTIL_VECTOR_INITIAL_SIZE, element_size);
    if (!self.data) LOG_RETURN("Failed to allocate memory for vector data.");
    return self;
}


void util_vector_free(vector_t* vec)
{
    free(vec->data);
}


void util_vector_push(vector_t* vec, void* element)
{

}


void util_vector_push_first(vector_t* vec, void* element)
{

}


void util_vector_insert(vector_t* vec, u64 index, void* element)
{

}