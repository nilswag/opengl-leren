#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "util/log.h"
#include "util/vector.h"

vector_t util_vector_init_size(u64 capacity, u64 element_size)
{
    vector_t self = { 0 };
    self.capacity = capacity;
    self.element_size = element_size;
    self.data = calloc(capacity, element_size);
    if (!self.data) LOG_RETURN_VAL((vector_t) { 0 }, "Failed to allocate memory for vector data.");
    return self;
}

vector_t util_vector_init(u64 element_size)
{
    vector_t self = { 0 };
    self.capacity = UTIL_VECTOR_INITIAL_SIZE;
    self.element_size = element_size;
    self.data = calloc(UTIL_VECTOR_INITIAL_SIZE, element_size);
    if (!self.data) LOG_RETURN_VAL((vector_t) { 0 }, "Failed to allocate memory for vector data.");
    return self;
}

void util_vector_free(vector_t* vec)
{
    free(vec->data);
}

static void _vector_resize(vector_t* vec, u64 new_size)
{
    void* new_data = calloc(new_size, vec->element_size);
    if (!new_data) LOG_RETURN("Failed to allocate memory for vector data.");
    memcpy(new_data, vec->data, vec->size * vec->element_size);
    free(vec->data);
    vec->data = new_data;
    vec->capacity = new_size;
}

void util_vector_push(vector_t* vec, void* element)
{
    if (vec->size >= vec->capacity) _vector_resize(vec, vec->capacity * 2);
    void* dest = (u8*)vec->data + vec->size * vec->element_size;
    memcpy(dest, element, vec->element_size);
    vec->size++;
}

void util_vector_push_first(vector_t* vec, void* element)
{
    if (vec->size >= vec->capacity) _vector_resize(vec, vec->capacity * 2);
    for (u64 i = vec->size; i > 0; i--)
    {
        void* dest = (u8*)vec->data + i * vec->element_size;
        void* src = (u8*)vec->data + (i - 1) * vec->element_size;
        memcpy(dest, src, vec->element_size);
    }
    memcpy(vec->data, element, vec->element_size);
    vec->size++;
}

void util_vector_insert(vector_t* vec, u64 index, void* element)
{
    if (index >= vec->size) LOG_RETURN("Index out of bounds for index: %llu", index);
    if (vec->size >= vec->capacity) _vector_resize(vec, vec->capacity * 2);
    for (u64 i = vec->size; i > index; i--)
    {
        void* dest = (u8*)vec->data + i * vec->element_size;
        void* src = (u8*)vec->data + (i - 1) * vec->element_size;
        memcpy(dest, src, vec->element_size);
    }
    void* dest = (u8*)vec->data + index * vec->element_size;
    memcpy(dest, element, vec->element_size);
    vec->size++;
}

void* util_vector_pop(vector_t* vec)
{
    if (vec->size < 1) LOG_RETURN_VAL(NULL, "Unable to pop element since vector is empty.");
    void* dest = (u8*)vec->data + (vec->size - 1) * vec->element_size;
    void* ret = malloc(vec->element_size);
    if (!ret) LOG_RETURN_VAL(NULL, "Failed to allocate memory for return value.");
    memcpy(ret, dest, vec->element_size);
    memset(dest, 0, vec->element_size);
    vec->size--;
    if ((f32)vec->size / vec->capacity <= 0.25f && vec->capacity > UTIL_VECTOR_MIN_CAPACITY) _vector_resize(vec, MAX(vec->capacity / 2, 1));
    return ret;
}

void* util_vector_pop_first(vector_t* vec)
{
    if (vec->size < 1) LOG_RETURN_VAL(NULL, "Unable to pop element since vector is empty.");

    if ((f32)vec->size / vec->capacity <= 0.25f && vec->capacity > UTIL_VECTOR_MIN_CAPACITY) _vector_resize(vec, MAX(vec->capacity / 2, 1));
}

void* util_vector_pop_at(vector_t* vec, u64 index)
{

}
