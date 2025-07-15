#include <string.h>
#include "log.h"
#include "gfx/window.h"
#include "util/vector.h"

window_t window;

static void init(void)
{
    LOG("DEBUG MODE ENABLED");

    vec_t v = util_vec_init(sizeof(i32));
    
    for (i32 i = 0; i < 5; i++)
        util_vec_push_back(&v, &i);

    for (u64 i = 0; i < 5; i++)
        LOG("%d", *(i32*)util_vec_pop_back(&v));
}

static char title_buffer[100];
static void tick(f32 delta)
{
    sprintf_s(title_buffer, sizeof(title_buffer), "ticks: %llu | fps: %u | frametime: %.2fms | size: %ux%u", window.ticks, window.fps, delta * 1e3, window.width, window.height);
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