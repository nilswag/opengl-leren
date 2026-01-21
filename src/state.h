#pragma once
#include <GLFW/glfw3.h>

typedef struct
{
    const char* title;
    int width, height;
    GLFWwindow* window;

    int running;
    size_t ticks;
    double dt;
} State;

extern State state;