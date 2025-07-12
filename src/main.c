#include <stdio.h>
#include <stdlib.h>

#include "util/io.h"
#include "gfx/window.h"


static void init(void)
{

}


static void tick(float delta)
{

}


static void render(void)
{
    
}


int main(void)
{
    window_t window = { 0 };
    gfx_window_init(&window, (window_callbacks_t) { init, tick, render });
    gfx_window_loop(&window);
    return 0;
}