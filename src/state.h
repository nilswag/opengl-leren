#pragma once
#include "util/core/defines.h"
#include "gfx/core/renderer.h"
#include "gfx/camera/camera.h"

typedef struct state
{
    bool running;
    u64 ticks;
    f64 dt;

    renderer renderer;
    camera camera;
} state;

extern state s;