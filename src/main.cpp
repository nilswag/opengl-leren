#include <glad/glad.h>
#include <glfw/glfw3.h>

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    while (!glfwWindowShouldClose(window)) glfwPollEvents();
    return 0;
}