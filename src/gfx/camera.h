#pragma once
#include "math/linmath.h"
#include "util/defines.h"

struct camera
{
    vec2f position;
    f32 zoom;
    mat3f view;
    mat3f proj;
};

void camera_init(struct camera* c, vec2 window_size);
void camera_update(struct camera* c);