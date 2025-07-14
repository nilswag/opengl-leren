#pragma once
#include <glfw/glfw3.h>

#include "defines.h"

typedef void (*gfx_window_on_init_fn)(void);
typedef void (*gfx_window_on_tick_fn)(f32 delta);
typedef void (*gfx_window_on_render_fn)(void);

typedef struct
{
    gfx_window_on_init_fn on_init;
    gfx_window_on_tick_fn on_tick;
    gfx_window_on_render_fn on_render;
} window_callbacks_t;

typedef struct
{
    GLFWwindow* handle;
    u32 width, height;
    u64 ticks;
    u32 fps;
    window_callbacks_t callbacks;
} window_t;

void gfx_window_init(window_t* window, window_callbacks_t callbacks);
void gfx_window_loop(window_t* window);

extern window_t window;