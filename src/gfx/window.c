#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "util/log.h"

static void _framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    w.size[0] = width;
    w.size[1] = height;
    glViewport(0, 0, width, height);
    // LOG_INFO("(%d, %d)\n", width, height);
}

void window_init(struct window* w)
{
    ASSERT(glfwInit(), "failed to initialize glfw\n");
    LOG_INFO("glfw initialized\n");

#if __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    w->size[0] = WINDOW_WIDTH;
    w->size[1] = WINDOW_HEIGHT;
    w->title = "Test";
    w->handle = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, w->title, NULL, NULL);

    ASSERT(w->handle, "failed to initialize glfw window\n");
    LOG_INFO("glfw window initialized\n");
    glfwMakeContextCurrent(w->handle);

    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "failed to initialize glad\n");
    LOG_INFO("glad initialized\n");

    glfwSetFramebufferSizeCallback(w->handle, _framebuffer_size_callback);
    // i don't completely understand why but this fixed fractional scaling issues on wayland
    i32 fbw, fbh;
    glfwGetFramebufferSize(w->handle, &fbw, &fbh);
    glViewport(0, 0, fbw, fbh);

    LOG_INFO("renderer: %s\n", glGetString(GL_RENDERER));
    LOG_INFO("opengl version: %s\n", glGetString(GL_VERSION));
}

void window_deinit(struct window* w)
{
    glfwDestroyWindow(w->handle);
    glfwTerminate();
}

void window_update(struct window* w)
{
    glfwSwapBuffers(w->handle);
}