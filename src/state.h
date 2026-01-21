#pragma once
#include <GLFW/glfw3.h>

struct State
{
    const char* title;
    int width, height;
    GLFWwindow* window;

    bool running;
    size_t ticks;
    double dt;
};

extern State state;