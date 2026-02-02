#pragma once
#include <GLFW/glfw3.h>
#include "math/linmath.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

struct window
{
    vec2 size;
    const char* title;
    GLFWwindow* handle;
};

extern struct window w;

void window_init(struct window* w);
void window_deinit(struct window* w);

void window_update(struct window* w);