#pragma once
#include "math/linmath.h"
#include "util/core/defines.h"

typedef struct camera
{
    vec2f position;
    f32 zoom;
    mat3f view;
    mat3f proj;
} camera;

void camera_init(camera* c, vec2 window_size);

void camera_update(camera* c);