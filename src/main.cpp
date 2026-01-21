#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "util/log.h"

int main()
{
    ASSERT(!glfwInit(), "Failed to initialize GLFW.\n");
    LOG_INFO("Hello World!\n");
}