#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gfx/window.h"


static void _framebuffer_size_callback(GLFWwindow* handle, int width, int height)
{
    window_t* window = (window_t*)glfwGetWindowUserPointer(handle);
    if (!window)
    {
        fputs("Failed to retrieve GLFW window user pointer.", stderr);
        return;
    }
    glViewport(0, 0, width, height);
    window->width = width;
    window->height = height;
}


void gfx_window_init(window_t* window, window_callbacks_t callbacks)
{
    if (!glfwInit())
    {
        fputs("Failed to initialize GLFW.", stderr);
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* handle = glfwCreateWindow(800, 800, "0 FPS", NULL, NULL);
    if (handle == NULL)
    {
        fputs("Failed to initialize GLFW window.", stderr);
        return;
    }
    glfwMakeContextCurrent(handle);
    glfwSwapInterval(1);
    window->handle = handle;
    window->width = window->height = 800;
    window->ticks = 0;
    window->fps = 0;
    window->callbacks = callbacks;
    glfwSetWindowUserPointer(handle, window);
    glfwSetFramebufferSizeCallback(handle, _framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fputs("Failed to initialize glad.", stderr);
        return;
    }
    glViewport(0, 0, 800, 800);
}


void gfx_window_loop(window_t* window)
{
    u64 frames = 0;
    f32 last = (f32)glfwGetTime();
    f32 accum = 0.0f;
    f32 accum_interval = 0.5f;

    if (window->callbacks.on_init)
        window->callbacks.on_init();

    while (!glfwWindowShouldClose(window->handle))
    { 
        glfwPollEvents();

        f32 first = (f32)glfwGetTime();
        f32 delta = first - last;
        last = first;

        accum += delta;
        frames++;

        if (accum >= accum_interval)
        {
            window->fps = (u32)(frames / accum_interval);
            frames = 0;
            accum = 0.0f;
        }

        if (window->callbacks.on_tick)
            window->callbacks.on_tick(delta);
        window->ticks++;

        glClear(GL_COLOR_BUFFER_BIT);
        if (window->callbacks.on_render)
            window->callbacks.on_render();
        glfwSwapBuffers(window->handle);
    }
}