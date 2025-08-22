#pragma once

#include <GLFW/glfw3.h> 

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    const char * getGlslVersion() const { return "#version 130"; }
    
    bool shouldClose() const { return glfwWindowShouldClose(window); }
    
    void setShouldClose(bool value) { glfwSetWindowShouldClose(window, value); }
    
    GLFWwindow* window;
};