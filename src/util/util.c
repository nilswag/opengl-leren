#include <stdint.h>

#include "util/util.h"

unsigned long util_fnv1a_hash(const char* key)
{
    unsigned long hash = FNV_OFFSET_BASIS;
    while (*key)
    {
        hash *= FNV_PRIME;
        hash ^= (uint8_t)*key++;
    }
    return hash;
}