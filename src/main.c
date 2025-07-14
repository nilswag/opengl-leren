#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/log.h"
#include "gfx/window.h"


window_t window;


static void init(void)
{
    
}

static char title_buffer[100];
static void tick(float delta)
{
    sprintf_s(title_buffer, sizeof(title_buffer), "TICKS: %llu, FPS: %u", window.ticks, window.fps);
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