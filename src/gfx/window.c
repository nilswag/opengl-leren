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
    window->width = (size_t)width;
    window->height = (size_t)height;
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

    GLFWwindow* handle = glfwCreateWindow(1000, 1000, "0 FPS", NULL, NULL);
    if (handle == NULL)
    {
        fputs("Failed to initialize GLFW window.", stderr);
        return;
    }
    glfwMakeContextCurrent(handle);
    glfwSwapInterval(1);
    window->handle = handle;
    window->width = window->height = 1000;
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
}


void gfx_window_loop(window_t* window)
{
    float frames = 0;
    float last = (float)glfwGetTime();
    float accum = 0.0f;
    float accum_interval = 0.5f;
    char title_buffer[100];

    if (window->callbacks.on_init)
        window->callbacks.on_init();

    while (!glfwWindowShouldClose(window->handle))
    { 
        glfwPollEvents();

        float first = (float)glfwGetTime();
        float delta = first - last;
        last = first;

        accum += delta;
        frames++;

        if (accum >= accum_interval)
        {
            frames /= accum_interval;
            snprintf(title_buffer, sizeof(title_buffer), "%.1f FPS", frames);
            glfwSetWindowTitle(window->handle, title_buffer);
            frames = 0;
            accum = 0.0f;
        }

        if (window->callbacks.on_tick)
            window->callbacks.on_tick(delta);

        glClear(GL_COLOR_BUFFER_BIT);
        if (window->callbacks.on_render)
            window->callbacks.on_render();
        glfwSwapBuffers(window->handle);
    }
}