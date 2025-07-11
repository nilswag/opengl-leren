#pragma once
#include <glfw/glfw3.h>


typedef void (*gfx_window_on_init_fn)(void);
typedef void (*gfx_window_on_tick_fn)(float delta);
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
    size_t width, height;
    size_t ticks;
    size_t fps;
    window_callbacks_t callbacks;
} window_t;


void gfx_window_init(
    window_t* window,
    window_callbacks_t callbacks
);


void gfx_window_loop(window_t* window);