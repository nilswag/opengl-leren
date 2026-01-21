#pragma once
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct
{
    const char* title;
    int width, height;
    GLFWwindow* window;

    bool running;
    size_t ticks;
    double dt;
} State;

extern State state;