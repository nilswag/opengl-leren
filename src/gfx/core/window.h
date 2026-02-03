#pragma once
#include <GLFW/glfw3.h>

#include "math/linmath.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct
{
    vec2 size;
    const char* title;
    GLFWwindow* handle;
} Window;

extern Window w;

void window_init(Window* w);
void window_deinit(Window* w);

void window_update(Window* w);