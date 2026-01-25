#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "util/defines.h"
#include "util/log.h"
#include "state.h"
#include "gfx/shader.h"

#include <math.h>

State state = { 0 };

static void _framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    state.width = width;
    state.height = height;
    glViewport(0, 0, width, height);
    // LOG_INFO("(%d, %d)\n", width, height);
}

f32 vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
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

    f64 last = glfwGetTime();

    u32 vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);

    u32 program = create_shader("vertex.glsl", "fragment.glsl");
    glUseProgram(program);
    i32 color_location = glGetUniformLocation(program, "_color");

    state.running = true;
    while (state.running && !glfwWindowShouldClose(state.window))
    {
        glfwPollEvents();

        double first = glfwGetTime();
        state.dt = first - last;
        last = first;

        f32 value = sin(glfwGetTime());
        glUniform4f(color_location, 0.0f, value, 0.0f, 1.0f);

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