#pragma once
#include "math/linmath.h"
#include "util/core/defines.h"

typedef struct
{
    vec2f position;
    f32 zoom;
    mat3f view;
    mat3f proj;
} Camera;

void camera_init(Camera* c, vec2 window_size);

void camera_update(Camera* c);