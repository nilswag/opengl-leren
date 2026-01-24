#pragma once
#include <GLFW/glfw3.h>
#include "util/defines.h"

typedef struct
{
    const char* title;
    i32 width, height;
    GLFWwindow* window;

    bool running;
    u64 ticks;
    f64 dt;
} State;

extern State state;