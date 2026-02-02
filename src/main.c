#include <GLFW/glfw3.h>
#include "state.h"
#include "gfx/window.h"
#include "util/defines.h"
#include "util/log.h"
#include <math.h>

struct state s = { 0 };
struct window w = { 0 };

static void _init(void)
{
    window_init(&w);
    camera_init(&s.camera, w.size);
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

    vec2f pos = { 0.0f, 0.0f };

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

        f32 speed = 250.0f * s.dt;
        f32 zoom  = 0.25f * s.dt;
        if (glfwGetKey(w.handle, GLFW_KEY_A)) pos[0] -= speed;
        if (glfwGetKey(w.handle, GLFW_KEY_D)) pos[0] += speed;
        if (glfwGetKey(w.handle, GLFW_KEY_W)) pos[1] += speed;
        if (glfwGetKey(w.handle, GLFW_KEY_S)) pos[1] -= speed;  

        if (glfwGetKey(w.handle, GLFW_KEY_LEFT)) s.camera.position[0] -= speed;
        if (glfwGetKey(w.handle, GLFW_KEY_RIGHT)) s.camera.position[0] += speed;
        if (glfwGetKey(w.handle, GLFW_KEY_UP)) s.camera.position[1] += speed;
        if (glfwGetKey(w.handle, GLFW_KEY_DOWN)) s.camera.position[1] -= speed;

        if (glfwGetKey(w.handle, GLFW_KEY_EQUAL)) s.camera.zoom += zoom;
        if (glfwGetKey(w.handle, GLFW_KEY_MINUS)) s.camera.zoom -= zoom;

        // rendering logic
        renderer_begin(&s.renderer);
        camera_update(&s.camera);
        renderer_set_camera(&s.renderer, PASS_WORLD, &s.camera);
        float t = (float)glfwGetTime() * 0.5f;

        vec4f color = {
            0.5f + 0.5f * sinf(t),
            0.5f + 0.5f * sinf(t + 2.0f),
            0.5f + 0.5f * sinf(t + 4.0f),
            1.0f
        };

        renderer_submit(&s.renderer, PASS_WORLD, (struct quad) {
            .pos   = { pos[0], pos[1] },
            .size  = { 100.0f, 100.0f },
            .rot   = 0.0f,
            .color = { color[0], color[1], color[2], color[3] }
        });

        renderer_submit(&s.renderer, PASS_WORLD, (struct quad) {
            .pos   = { 120.0f, 250.0f },
            .size  = { 120.0f, 40.0f },
            .rot   = 0.0f,
            .color = { 1.0f, 0.0f, 0.0f, 1.0f }
        });

        renderer_flush(&s.renderer);
        window_update(&w);
    }

    _deinit();
    
    return 0;
}
