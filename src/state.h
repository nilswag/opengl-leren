#pragma once
#include <GLFW/glfw3.h>
#include "util/defines.h"
#include "gfx/renderer.h"

struct state
{
    const char* title;
    i32 width, height;
    GLFWwindow* window;

    bool running;
    u64 ticks;
    f64 dt;

    struct renderer renderer;
};

extern struct state state;