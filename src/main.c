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
    // Front face (red)
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  // top-left
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  // top-right
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  // bottom-right
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  // bottom-left

    // Back face (green)
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,

    // Left face (blue)
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,

    // Right face (yellow)
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,

     // Top face (cyan)
     -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
     -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,

     // Bottom face (magenta)
     -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 2,  2, 3, 0,        // front
    4, 5, 6,  6, 7, 4,        // back
    8, 9,10, 10,11, 8,        // left
   12,13,14, 14,15,12,        // right
   16,17,18, 18,19,16,        // top
   20,21,22, 22,23,20         // bottom
};


static void _framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(void)
{
    if (!glfwInit())
    {
        fputs("Failed to initialize GLFW.", stderr);
        return -1;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "0 FPS", NULL, NULL);
    if (window == NULL)
    {
        fputs("Failed to initialize GLFW window.", stderr);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, _framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fputs("Failed to initialize glad.", stderr);
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);

    // ======================================

    char* vertex_src = util_read_file("resources/shaders/basic/vertex.glsl");
    char* fragment_src = util_read_file("resources/shaders/basic/fragment.glsl");
    Shader shader = gfx_shader_init(vertex_src, fragment_src);
    gfx_shader_use(&shader);
    free(vertex_src);
    free(fragment_src);

    Matf4x4 model = MATH_MATRIX_IDENTITY_4x4f;
    Matf4x4 view = math_matrix_lookat((Vec3f) { 0.0f, 0.0f, 3.0f }, (Vec3f) { 0.0f, 0.0f, 0.0f });
    Matf4x4 proj = math_matrix_proj_pers(60.0f, 1.0f, 0.1f, 100.0f);

    Mesh mesh = { 0 };

    VertexAttribute vertex_attributes[] = {
        { .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = 0 },
        { .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = 3 * sizeof(float) }
    };

    gfx_mesh_init(&mesh, indices, 36, vertex_attributes, 2, vertex_data, 24, 6 * sizeof(float));

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

        math_matrix_rotate4x4(&model, delta * 45.0f, delta * 45.0f, 0.0f);
        gfx_shader_set_matrix4f(&shader, "view", &view);
        gfx_shader_set_matrix4f(&shader, "model", &model);
        gfx_shader_set_matrix4f(&shader, "proj", &proj);

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