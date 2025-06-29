#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/io.h"
#include "gfx/shader.h"
#include "gfx/map.h"
#include "gfx/mesh.h"
#include "math/matrix.h"

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


    char* vertex_src = util_read_file("resources/shaders/basic/vertex.glsl");
    char* fragment_src = util_read_file("resources/shaders/basic/fragment.glsl");
    shader_t shader = gfx_shader_init(vertex_src, fragment_src);
    gfx_shader_use(&shader);
    free(vertex_src);
    free(fragment_src);

    float identity[] = MATH_IDENTITY_MATRIX_4x4;

    mesh_t mesh = { 0 };

    float vertex_data[] = {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.0f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    };

    vertex_attribute_t vertex_attributes[] = {
        { .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = 0.0f },
        { .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = 3 * sizeof(float) }
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    gfx_mesh_init(&mesh, indices, 3, vertex_attributes, 2, vertex_data, 3, 6 * sizeof(float));

    // ======================================
    float last = (float)glfwGetTime();
    float accumulator = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        float now = (float)glfwGetTime();
        float delta = now - last;
        last = now;
        accumulator += delta;

        if (accumulator >= 0.25f)
        {
            accumulator = 0.0f;
            int fps = (int)(1 / delta);
            char buffer[100];
            sprintf_s(buffer, sizeof(buffer), "%d FPS", fps);
            glfwSetWindowTitle(window, buffer);
        }

        math_matrix_rotate_y(identity, 100.0f * delta);
        gfx_shader_set_matrix4fv(&shader, "transform", identity);

        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        gfx_mesh_render(&mesh);
        glfwSwapBuffers(window);
    }

    // ======================================

    gfx_mesh_free(&mesh);
    gfx_shader_free(&shader);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}