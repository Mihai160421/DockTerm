#include "Application.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <iostream>

void Application::run() {
    isRunning = true;
    std::cout << "Dockterm application is running...\n";

    // Create main window
    mainWindow = new Window(1280, 800, "DockTerm");
    if (mainWindow->window == nullptr) {
        std::cerr << "Failed to create main window.\n";
        return;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();


    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->mainWindow->window, true);
    ImGui_ImplOpenGL3_Init(this->mainWindow->getGlslVersion());

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    io.Fonts->AddFontFromFileTTF("assets/fonts/RobotoMonoNerdFont-Regular.ttf", 20.0f);
    io.FontDefault = io.Fonts->Fonts.back();

    // Main loop
    while (!this->mainWindow->shouldClose() && isRunning)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(this->mainWindow->window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Here we render all UI Stuff
        this->render();

        // Rendering
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(this->mainWindow->window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(this->mainWindow->window);
    }

    cleanup();
}

void Application::stop() {
    std::cout << "Dockterm application is stopping...\n";
    isRunning = false;
}

void Application::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->mainWindow->window);
    glfwTerminate();
}

void Application::RenderMenuBar()
{
    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New")) {
                // TODO
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                this->mainWindow->setShouldClose(true);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About")) {
            }
            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Debug"))
        {
            if (ImGui::MenuItem("SpawnTerminalView")) {
                if(this->terminalView == nullptr)
                {
                    this->terminalView = new TerminalView();
                }
            }
            ImGui::EndMenu();
        }

        // Show fps on the right side of the menu bar
        ImGui::SameLine(ImGui::GetWindowWidth() - 100); 
        ImGui::Text("FPS: %.1f", io.Framerate);

        ImGui::EndMainMenuBar();
    }

}

void Application::render() {
    RenderMenuBar();

    if(this->terminalView != nullptr) {
        this->terminalView->render();
    }
}