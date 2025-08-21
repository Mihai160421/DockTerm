#include "Application.hpp"

#include <iostream>
#include <thread>
#include <chrono>

void Application::run() {
    isRunning = true;
    std::cout << "Dockterm application is running...\n";
    
    while (isRunning)
    {
        std::cout << "Working hard.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Application::stop() {
    std::cout << "Dockterm application is stopping...\n";
    isRunning = false;
}
