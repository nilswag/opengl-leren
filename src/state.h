#pragma once
#include "util/core/defines.h"
#include "gfx/core/renderer.h"
#include "gfx/camera/camera.h"

typedef struct
{
    bool running;
    u64 ticks;
    f64 dt;

    Renderer renderer;
    Camera camera;
} State;

extern State s;