#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit()) std::cout << "failed to initialize glfw" << std::endl;
	GLFWwindow* window = nullptr;
	window = glfwCreateWindow(1280, 720, "testing", nullptr, nullptr);
	if (window == nullptr) std::cout << "failed to create glfw window" << std::endl;
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "failed to initialize glad" << std::endl;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}