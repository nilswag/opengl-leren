#pragma once
#include <GLFW/glfw3.h>
#include "util/defines.h"
#include "gfx/renderer.h"
#include "gfx/camera.h"

struct state
{
    bool running;
    u64 ticks;
    f64 dt;

    struct renderer renderer;
    struct camera camera;
};

extern struct state s;