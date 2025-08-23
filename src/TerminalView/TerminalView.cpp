#include "TerminalView.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

TerminalView::TerminalView()
{
    if(this->screenBuffer == nullptr)
    {
        screenBuffer = new ScreenBuffer(0,0);
    }

    if (this->scrollBuffer == nullptr)
    {
        scrollBuffer = new ScrollBuffer();
    }
}

void TerminalView::render() {
    ImGuiIO& io = ImGui::GetIO();
    
    // Set the next window position and size to fill the main viewport below the menu bar
    float menu_height = ImGui::GetFrameHeight(); // înălțime standard pentru elemente UI
    ImVec2 window_size = ImVec2(io.DisplaySize.x, io.DisplaySize.y-menu_height);
    ImGui::SetNextWindowPos(ImVec2(0, menu_height));                           
    ImGui::SetNextWindowSize(window_size);
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin(name, NULL, ImGuiWindowFlags_NoCollapse 
                                    | ImGuiWindowFlags_NoResize 
                                    | ImGuiWindowFlags_NoMove 
                                    | ImGuiWindowFlags_AlwaysAutoResize 
                                    | ImGuiWindowFlags_NoBringToFrontOnFocus);

 
    ImVec2 min = ImGui::GetWindowContentRegionMin();
    ImVec2 max = ImGui::GetWindowContentRegionMax();
    ImVec2 size = ImVec2(max.x - min.x, max.y - min.y);

    
    ImVec2 char_size = io.Fonts->Fonts.back()->CalcTextSizeA(16.0f, FLT_MAX, 0.0f, "W");
    int cols = static_cast<int>(size.x / char_size.x);
    int rows = static_cast<int>(size.y / char_size.y);

    if (cols != screenBuffer->getWidth() || rows != screenBuffer->getHeight())
    {
        screenBuffer->resize(cols, rows);
    }



    // Simulate a dummy scrollbar for the scroll buffer
    ImGui::Dummy(ImVec2(0, (this->scrollBuffer->GetRowsCount() + this->screenBuffer->getHeight()) * char_size.y)); // Leave space for scrollbar


    ImGui::SetCursorPosY(min.y);
    ImGui::SetCursorPosX(min.x);
   
    RenderScrollBuffer();
    ImGui::Separator();
    
    ImGui::SetCursorPosY(min.y);
    ImGui::SetCursorPosX(min.x);
   
    RenderScreenBuffer();

    ImGui::End();

    ImGui::PopStyleVar();

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

    //Button for pushing a text to scroll buffer
    if(ImGui::Button("Push to ScrollBuffer"))
    {
        std::vector<Cell> row;
        std::string text = "Hello World!";
        for(char c : text)
        {
            Cell cell;
            cell.character = c;
            cell.fgColor = IM_COL32(255, 255, 255, 255);
            cell.bgColor = IM_COL32(0, 0, 0, 255);
            row.push_back(cell);
        }
        scrollBuffer->PushRow(row);
    }

    ImGui::End();

}

void TerminalView::RenderScrollBuffer()
{

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

    // Draw Cursor
    ImVec2 cursorPos = screenBuffer->Getcursor();
    ImVec2 cursor_screen_pos = ImVec2(pos.x + cursorPos.x * char_size.x, pos.y + cursorPos.y * char_size.y);
    // Add fill rectangle for cursor
    draw_list->AddRectFilled(cursor_screen_pos, ImVec2(cursor_screen_pos.x + char_size.x, cursor_screen_pos.y + char_size.y), IM_COL32(255, 255, 255, 255));
}
