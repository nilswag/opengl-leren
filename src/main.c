#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/log.h"
#include "gfx/window.h"


window_t window;


static void init(void)
{
    LOG("DEBUG MODE ENABLED");
}

static char title_buffer[100];
static void tick(f32 delta)
{
    sprintf_s(title_buffer, sizeof(title_buffer), "ticks: %llu, fps: %u, frametime: %.2fms, size: %ux%u", window.ticks, window.fps, delta * 1e3, window.width, window.height);
    glfwSetWindowTitle(window.handle, title_buffer);
}


static void render(void)
{
    
}


int main(void)
{
    gfx_window_init(&window, (window_callbacks_t) { init, tick, render });
    gfx_window_loop(&window);
    return 0;
}