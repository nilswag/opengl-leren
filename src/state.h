#pragma once
#include "util/core/defines.h"
#include "gfx/core/renderer.h"
#include "gfx/camera/camera.h"

struct renderer;
struct camera;

struct state
{
    bool running;
    u64 ticks;
    f64 dt;

    struct renderer renderer;
    struct camera camera;
};

extern struct state s;