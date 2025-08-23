#include "TerminalView.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

TerminalView::TerminalView()
{
    if(this->screenBuffer == nullptr)
    {
        screenBuffer = new ScreenBuffer(1000,1000);


        // Initialize screenBuffer with some content for testing 
        for(int r = 0; r < screenBuffer->getHeight(); r++) {
            for(int c = 0; c < screenBuffer->getWidth(); c++) {
                Cell& cell = screenBuffer->at(r, c);
                cell.character = (c % 10) + '0'; // Fill with digits 0-9
            }
        }
    }
}

void TerminalView::render() {
    ImGuiIO& io = ImGui::GetIO();
    
    // Set the next window position and size to fill the main viewport below the menu bar
    float menu_height = ImGui::GetFrameHeight(); // înălțime standard pentru elemente UI
    ImVec2 window_size = ImVec2(io.DisplaySize.x, io.DisplaySize.y-menu_height);
    ImGui::SetNextWindowPos(ImVec2(0, menu_height));                           
    ImGui::SetNextWindowSize(window_size);
    
    // Get size of a single character in the current font and calculate rows and columns that fit
    ImVec2 char_size = io.Fonts->Fonts.back()->CalcTextSizeA(16.0f, FLT_MAX, 0.0f, "W");
    int cols = static_cast<int>(window_size.x / char_size.x);
    int rows = static_cast<int>(window_size.y / char_size.y);

    if (cols != screenBuffer->getWidth() || rows != screenBuffer->getHeight())
    {
        screenBuffer->resize(cols, rows);
    }


    ImGui::Begin(name, NULL, ImGuiWindowFlags_NoCollapse 
                                    | ImGuiWindowFlags_NoResize 
                                    | ImGuiWindowFlags_NoMove 
                                    | ImGuiWindowFlags_AlwaysAutoResize 
                                    | ImGuiWindowFlags_NoBringToFrontOnFocus);

    RenderScreenBuffer();

    ImGui::End();


    if(tDebugWindow) {
        renderDebugWindow();
    }
}

void TerminalView::renderDebugWindow()
{
    // cocnat Debug to name for unique window title
    std::string debugWindowName = std::string(name) + " Debug";

    ImGui::Begin(debugWindowName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("TerminalView Debug Info");
    ImGui::Text("ScreenBuffer Size: %d cols x %d rows", screenBuffer->getWidth(), screenBuffer->getHeight());

    ImGui::End();

}

void TerminalView::RenderScreenBuffer()
{
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImVec2 char_size = io.Fonts->Fonts.back()->CalcTextSizeA(16.0f, FLT_MAX, 0.0f, "W");

    for(int r = 0; r < screenBuffer->getHeight(); r++) {
        for(int c = 0; c < screenBuffer->getWidth(); c++) {
            Cell& cell = screenBuffer->at(r, c);
            ImVec2 cell_pos = ImVec2(pos.x + c * char_size.x, pos.y + r * char_size.y);

            // Draw background
            draw_list->AddRectFilled(cell_pos, ImVec2(cell_pos.x + char_size.x, cell_pos.y + char_size.y), cell.bgColor);

            // Draw character
            draw_list->AddText(io.Fonts->Fonts.back(), 16.0f, cell_pos, cell.fgColor, std::string(1, cell.character).c_str());
        }
    }
}
