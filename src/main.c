#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdbool.h>
#include "util/log.h"
#include "state.h"
#include "util/io.h"

State state = { 0 };

static void _framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    state.width = width;
    state.height = height;
    glViewport(0, 0, width, height);
    // LOG_INFO("(%d, %d)\n", width, height);
}

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

GLuint compile_shader(const char* path, GLenum type)
{
    GLuint id = glCreateShader(type);
    const char* src = read_file(path);

    glShaderSource(id, 1, &src, NULL);
    LOG_INFO("compiling shader with path %s\n", path);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int length = 512;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetShaderInfoLog(id, length, NULL, log);
        LOG_WARN("error during shader compilation with path %s: %s\n", path, log);
    } else LOG_INFO("compiled shader with path %s\n", path);

    return id;
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

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertex_shader = compile_shader("vertex.glsl", GL_VERTEX_SHADER);
    GLuint fragment_shader = compile_shader("fragment.glsl", GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        int length = 512;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetProgramInfoLog(program, length, NULL, log);
        LOG_WARN("error during shader linking: %s\n", log);
    } else LOG_INFO("linked shader\n");

    glUseProgram(program);

    state.running = true;
    while (state.running && !glfwWindowShouldClose(state.window))
    {
        double first = glfwGetTime();
        state.dt = first - last;
        last = first;

        glfwPollEvents();

        glClearColor(.0f, .0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
        glfwSwapBuffers(state.window);
    }

    glfwDestroyWindow(state.window);
    glfwTerminate();
    return 0;
}