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

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    mesh_t mesh = { 0 };
    gfx_mesh_init(&mesh, vertices, 9, indices, 3);

    // ======================================
    double max_frame_time = 1.0 / 1.0;
    double accumulator = 0.0;
    double last = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        double now = glfwGetTime();
        double delta = now - last;
        last = now;

        math_matrix_rotate(identity, 100.0f * delta, 0.0f, 0.0f);
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