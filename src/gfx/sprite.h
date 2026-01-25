#pragma once
#include "math/linmath.h"
#include "util/defines.h"

typedef struct
{
    Mat3f transform;
    f32 x, y;
    f32 sx, sy;
    f32 rot;
} Sprite;
