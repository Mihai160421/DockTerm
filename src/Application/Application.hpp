#pragma once

#include "Window/Window.hpp"
#include "TerminalView/TerminalView.hpp"

class Application {
public:
    Application() = default;
    ~Application() = default;

    void run();
    void stop();

private:
    bool isRunning = false;
    Window* mainWindow = nullptr;
    TerminalView* terminalView = nullptr;

    void cleanup();

    void render();
    void RenderMenuBar();
};