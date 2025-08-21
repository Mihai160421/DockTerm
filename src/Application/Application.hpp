#pragma once

class Application {
public:
    Application() = default;
    ~Application() = default;

    void run();
    void stop();

private:
    bool isRunning = false;
};