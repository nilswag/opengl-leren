#include "state.h"
#include "gfx/window.h"
#include "util/defines.h"
#include "util/log.h"

struct state s = { 0 };
struct window w = { 0 };

static void _init(void)
{
    window_init(&w);
    renderer_init(&s.renderer);
    camera_init(&s.camera, w.size);
}

static void _deinit(void)
{
    renderer_deinit(&s.renderer);
    window_deinit(&w);
}

int main(void)
{
    _init();

    f64 last = glfwGetTime();
    f64 timer = 0.0;

    s.running = true;
    while (s.running && !glfwWindowShouldClose(w.handle))
    {
        glfwPollEvents();

        // state telemetry data
        double first = glfwGetTime();
        s.dt = first - last;
        last = first;
        s.ticks++;

        // updating logic
        timer += s.dt;
        if (timer >= 1.0)
        {
            timer = 0.0;
            LOG_INFO("%d fps\n", (int)(1 / s.dt));
        }
        
        // rendering logic
        render_pass_begin(&s.renderer);
        renderer_set_camera(&s.renderer, &s.camera);
        // actual rendering stuff
        renderer_flush(&s.renderer);
        render_pass_end(&s.renderer);
        window_update(&w);
    }

    _deinit();
    
    return 0;
}
