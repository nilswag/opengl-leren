#pragma once
#include <GLFW/glfw3.h>
#include "util/defines.h"
#include "gfx/renderer.h"
#include "math/linmath.h"

struct state
{
    const char* title;
    i32 width, height;
    GLFWwindow* window;

    bool running;
    u64 ticks;
    f64 dt;

    i32 view_location;
    mat3f view;

    struct renderer renderer;
};

extern struct state s;