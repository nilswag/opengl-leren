#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/io.h"

float vertices[] = {
    -0.5f, -0.5f,  0.0f,
     0.0f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f
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

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    char* vertex_src = util_read_file("resources/shaders/basic/vertex.glsl");
    char* fragment_src = util_read_file("resources/shaders/basic/fragment.glsl");
    
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const char* const*)&vertex_src, NULL);
    glCompileShader(vertex_shader);

    unsigned int success = 1;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        unsigned int length = 0;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
        char* info_log = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(vertex_shader, length, NULL, info_log);
        fprintf(stderr, "Failed to compile vertex_shader: %s\n", info_log);
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const char* const*)&fragment_src, NULL);
    glCompileShader(fragment_shader);

    success = 1;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        unsigned int length = 0;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
        char* info_log = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(fragment_shader, length, NULL, info_log);
        fprintf(stderr, "Failed to compile fragment_shader: %s\n", info_log);
    }

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    success = 1;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        unsigned int length = 0;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &length);
        char* info_log = (char*)malloc(length * sizeof(char));
        glGetProgramInfoLog(shader_program, length, NULL, info_log);
        fprintf(stderr, "Failed to link shader program: %s\n", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    free(vertex_src);
    free(fragment_src);

    glUseProgram(shader_program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ======================================

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}