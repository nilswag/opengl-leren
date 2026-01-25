#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "util/defines.h"
#include "util/log.h"
#include "state.h"

#include "math/matrix.h"

State state = { 0 };

static void _framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    state.width = width;
    state.height = height;
    glViewport(0, 0, width, height);
    // LOG_INFO("(%d, %d)\n", width, height);
}

int main()
{
    ASSERT(glfwInit(), "failed to initialize glfw\n");
    LOG_INFO("glfw initialized\n");

    state.width = 1000;
    state.height = 1000;
    state.title = "test";
    state.window = glfwCreateWindow(state.width, state.height, state.title, NULL, NULL);
    ASSERT(state.window, "failed to initialize glfw window\n");
    LOG_INFO("glfw window initialized\n");
    glfwMakeContextCurrent(state.window);

    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "failed to initialize glad\n");
    LOG_INFO("glad initialized\n");
    glViewport(0, 0, state.width, state.height);
    glfwSetFramebufferSizeCallback(state.window, _framebuffer_size_callback);

    LOG_INFO("renderer: %s\n", glGetString(GL_RENDERER));
    LOG_INFO("opengl version: %s\n", glGetString(GL_VERSION));

    Mat2x2f mat;
    _mat_zero_dynamic(mat, 2, 2);

    f64 last = glfwGetTime();

    state.running = true;
    while (state.running && !glfwWindowShouldClose(state.window))
    {
        glfwPollEvents();

        double first = glfwGetTime();
        state.dt = first - last;
        last = first;

        glClearColor(.0f, .0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(state.window);
    }

    glfwDestroyWindow(state.window);
    glfwTerminate();
    return 0;
}