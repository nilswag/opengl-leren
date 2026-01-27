#include <glad/glad.h>
#include <glfw/glfw3.h>
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

static void _init()
{
    ASSERT(glfwInit(), "failed to initialize glfw\n");
    LOG_INFO("glfw initialized\n");

    s.width = 1000;
    s.height = 1000;
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

static void _deinit()
{
    renderer_deinit(&s.renderer);
    glfwDestroyWindow(s.window);
    glfwTerminate();
}

int main()
{
    _init();

    f64 last = glfwGetTime();

    s.running = true;
    while (s.running && !glfwWindowShouldClose(s.window))
    {
        glfwPollEvents();

        double first = glfwGetTime();
        s.dt = first - last;
        last = first;

        glClearColor(.0f, .0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render_pass_begin(&s.renderer);
        render_quad(&s.renderer, (struct quad) { 0, 0, 1, 1, 0.0f });
        render_pass_end(&s.renderer);

        glfwSwapBuffers(s.window);
    }

    _deinit();
    
    return 0;
}