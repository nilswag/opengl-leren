#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/io.h"
#include "gfx/shader.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 2
};

int main(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    if (!glfwInit())
    {
        fputs("Failed to initialize GLFW.", stderr);
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "glfw window", NULL, NULL);
    if (window == NULL)
    {
        fputs("Failed to initialize GLFW window.", stderr);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fputs("Failed to initialize glad.", stderr);
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 1280, 720);

    // ======================================

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    char* vertex_src = util_read_file("resources/shaders/basic/vertex.glsl");
    char* fragment_src = util_read_file("resources/shaders/basic/fragment.glsl");
    Shader shader = gfx_shader_init(vertex_src, fragment_src);
    gfx_shader_use(&shader);
    free(vertex_src);
    free(fragment_src);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // ======================================

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }

    gfx_shader_destroy(&shader);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}