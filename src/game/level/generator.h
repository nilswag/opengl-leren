#pragma once
#include "math/linmath.h"
#include "util/core/defines.h"

#define MAX_ROOM_SIZE ((vec2) { 50, 50 })
#define MIN_ROOM_SIZE ((vec2) { 12, 12})
#define MAX_ROOMS 10
#define MIN_ROOMS 5

typedef struct room
{
    vec2 pos;
    vec2 size;
} room;

void generate_rooms(void);