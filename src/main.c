#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/io.h"
#include "gfx/shader.h"
#include "gfx/map.h"
#include "gfx/mesh.h"
#include "math/matrix.h"


float vertex_data[] = {
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f
};


unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,

    4, 0, 3,
    3, 7, 4,

    1, 5, 6,
    6, 2, 1,

    4, 5, 1,
    1, 0, 4,

    3, 2, 6,
    6, 7, 3
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

    GLFWwindow* window = glfwCreateWindow(1280, 720, "0 FPS", NULL, NULL);
    if (window == NULL)
    {
        fputs("Failed to initialize GLFW window.", stderr);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fputs("Failed to initialize glad.", stderr);
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 1280, 720);
    glEnable(GL_DEPTH_TEST);


    // ======================================

    char* vertex_src = util_read_file("resources/shaders/basic/vertex.glsl");
    char* fragment_src = util_read_file("resources/shaders/basic/fragment.glsl");
    shader_t shader = gfx_shader_init(vertex_src, fragment_src);
    gfx_shader_use(&shader);
    free(vertex_src);
    free(fragment_src);

    mat4x4f_t model = MATH_MATRIX_IDENTITY_4x4f;

    mesh_t mesh = { 0 };

    vertex_attribute_t vertex_attributes[] = {
        { .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = 0 },
        { .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = 3 * sizeof(float) }
    };

    gfx_mesh_init(&mesh, indices, 36, vertex_attributes, 2, vertex_data, 8, 6 * sizeof(float));

    // ======================================

    float last = (float)glfwGetTime();
    float accumulator = 0.0f;
    size_t frames = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        float now = (float)glfwGetTime();
        float delta = now - last;
        last = now;
        accumulator += delta;
        frames++;

        if (accumulator >= 0.5f)
        {
            int fps = (int)(frames / accumulator);
            frames = 0;
            accumulator = 0.0f;
            char buffer[100];
            sprintf_s(buffer, sizeof(buffer), "%d FPS", fps);
            glfwSetWindowTitle(window, buffer);
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        math_matrix_rotate4x4_y(&model, delta * 90.0f);
        gfx_shader_set_matrix4fv(&shader, "model", &model);

        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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