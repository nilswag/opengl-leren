#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdbool.h>
#include "util/log.h"
#include "state.h"

State state = { 0 };

static void _framebuffer_size_callback(GLFWwindow* window, int width, int height)
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

    state.width = 800;
    state.height = 800;
    state.title = "test";
    state.window = glfwCreateWindow(state.width, state.height, state.title, NULL, NULL);
    ASSERT(state.window, "failed to initialize glfw window\n");
    LOG_INFO("glfw window initialized\n");
    glfwMakeContextCurrent(state.window);

    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "failed to initialize glad\n");
    LOG_INFO("glad initialized\n");
    glViewport(0, 0, state.width, state.height);
    glfwSetFramebufferSizeCallback(state.window, _framebuffer_size_callback);

    double last = glfwGetTime();

    state.running = true;
    while (state.running && !glfwWindowShouldClose(state.window))
    {
        double first = glfwGetTime();
        state.dt = first - last;
        last = first;

        glfwPollEvents();

        glClearColor(.0f, .0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // render stuff
        glfwSwapBuffers(state.window);
    }

    glfwDestroyWindow(state.window);
    glfwTerminate();
    return 0;
}