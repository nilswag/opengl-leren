#include "state.h"
#include "gfx/window.h"
#include "util/defines.h"
#include "util/log.h"

struct state s = { 0 };
struct window w = { 0 };

static void _init(void)
{
    window_init(&w);
    camera_init(&s.camera, (vec2) { 400, 400 });
    renderer_init(&s.renderer);
}

static void _deinit(void)
{
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
        renderer_begin(&s.renderer);
        camera_update(&s.camera);
        renderer_set_camera(&s.renderer, PASS_WORLD, &s.camera);
        renderer_submit(&s.renderer, PASS_WORLD, (struct quad) { 
            .pos = { 0.0f, 100.0f }, .size = { 100.0f, 100.0f }, .rot = 0.0f, .color = { 1.0f, 0.0f, 0.0f, 1.0f }
        });
        renderer_flush(&s.renderer);
        window_update(&w);
    }

    _deinit();
    
    return 0;
}
