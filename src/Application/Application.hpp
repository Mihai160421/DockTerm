#pragma once

#include "Window/Window.hpp"

class Application {
public:
    Application() = default;
    ~Application() = default;

    void run();
    void stop();

private:
    bool isRunning = false;
    Window* mainWindow = nullptr;

    void cleanup();

    void render();
    void RenderMenuBar();
};