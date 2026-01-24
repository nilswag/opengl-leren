#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdbool.h>
#include "util/log.h"
#include "state.h"
#include "gfx/shader.h"

State state = { 0 };

static void _framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    state.width = width;
    state.height = height;
    glViewport(0, 0, width, height);
    // LOG_INFO("(%d, %d)\n", width, height);
}

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

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

    double last = glfwGetTime();

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint program = create_shader("vertex.glsl", "fragment.glsl");
    glUseProgram(program);

    state.running = true;
    while (state.running && !glfwWindowShouldClose(state.window))
    {
        glfwPollEvents();

        double first = glfwGetTime();
        state.dt = first - last;
        last = first;

        glClearColor(.0f, .0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
        glfwSwapBuffers(state.window);
    }

    glDeleteProgram(program);
    glfwDestroyWindow(state.window);
    glfwTerminate();
    return 0;
}