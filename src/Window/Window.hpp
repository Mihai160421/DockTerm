#pragma once

#include <GLFW/glfw3.h> 

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    GLFWwindow* window;

    const char * getGlslVersion() const { return "#version 130"; }

    bool shouldClose() const { return glfwWindowShouldClose(window); }
};