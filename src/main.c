#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "util/defines.h"
#include "util/log.h"
#include "state.h"
#include "gfx/renderer.h"


struct state s = { 0 };

static void _framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    s.width = width;
    s.height = height;
    glViewport(0, 0, width, height);
    // LOG_INFO("(%d, %d)\n", width, height);
}

static void _init(void)
{
    ASSERT(glfwInit(), "failed to initialize glfw\n");
    LOG_INFO("glfw initialized\n");

    s.width = 800;
    s.height = 800;
    s.title = "test";
    s.window = glfwCreateWindow(s.width, s.height, s.title, NULL, NULL);
    ASSERT(s.window, "failed to initialize glfw window\n");
    LOG_INFO("glfw window initialized\n");
    glfwMakeContextCurrent(s.window);

    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "failed to initialize glad\n");
    LOG_INFO("glad initialized\n");
    glViewport(0, 0, s.width, s.height);
    glfwSetFramebufferSizeCallback(s.window, _framebuffer_size_callback);

    LOG_INFO("renderer: %s\n", glGetString(GL_RENDERER));
    LOG_INFO("opengl version: %s\n", glGetString(GL_VERSION));

    renderer_init(&s.renderer);
}

static void _deinit(void)
{
    renderer_deinit(&s.renderer);
    glfwDestroyWindow(s.window);
    glfwTerminate();
}

int main(void)
{
    _init();

    f64 last = glfwGetTime();

    f64 timer = 0.0;

    f32 pos[2] = { 0.0f, 0.0f};
    f32 speed = 0.25f;

    s.running = true;
    while (s.running && !glfwWindowShouldClose(s.window))
    {
        glfwPollEvents();

        double first = glfwGetTime();
        s.dt = first - last;
        last = first;

        if (glfwGetKey(s.window, GLFW_KEY_LEFT)) pos[0] -= speed * s.dt;
        if (glfwGetKey(s.window, GLFW_KEY_RIGHT)) pos[0] += speed * s.dt;
        if (glfwGetKey(s.window, GLFW_KEY_UP)) pos[1] += speed * s.dt;
        if (glfwGetKey(s.window, GLFW_KEY_DOWN)) pos[1] -= speed * s.dt;

        // LOG_INFO("%f: %f\n", pos[0], pos[1]);

        timer += s.dt;
        if (timer >= 1.0)
        {
            timer = 0.0;
            LOG_INFO("%d fps\n", (int)(1 / s.dt));
        }

        glClearColor(.0f, .0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_pass_begin(&s.renderer);
        render_quad(&s.renderer, (struct quad) { pos[0], pos[1], 1.0f, 1.0f, 0.0f });
        renderer_flush(&s.renderer);
        render_pass_end(&s.renderer);

        glfwSwapBuffers(s.window);
    }

    _deinit();
    
    return 0;
}
