#pragma once

#define FNV_OFFSET_BASIS 0xcbf29ce484222325
#define FNV_PRIME 0x100000001b3

unsigned long util_fnv1a_hash(const char* key);