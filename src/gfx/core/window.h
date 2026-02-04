#pragma once
#include <GLFW/glfw3.h>

#include "math/linmath.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct window
{
    vec2 size;
    const char* title;
    GLFWwindow* handle;
} window;

extern window w;

void window_init(window* w);
void window_deinit(window* w);

void window_update(window* w);