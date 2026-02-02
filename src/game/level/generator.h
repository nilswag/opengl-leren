#pragma once
#include "util/defines.h"

#define TILE_SIZE 16
#define WORLD_SIZE 64
#define TILE_INDEX(x, y) ((y) * WORLD_SIZE + (x))

struct level
{
    u32 tiles[WORLD_SIZE * WORLD_SIZE];
};

void generate_rooms(struct level* level);