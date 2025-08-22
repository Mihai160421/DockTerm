#include "TerminalView.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

TerminalView::TerminalView() {
    // Initialization if necessary
}

void TerminalView::render() {
    float menu_height = ImGui::GetFrameHeight(); // înălțime standard pentru elemente UI
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_size = ImVec2(io.DisplaySize.x, io.DisplaySize.y-menu_height);

    ImGui::SetNextWindowPos(ImVec2(0, menu_height));                           
    ImGui::SetNextWindowSize(window_size);
    
/*  
    Handle the resizing of screenBuffer if necessary
*/



    ImGui::Begin(name, NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::End();
}