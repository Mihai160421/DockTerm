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
    ImGui::SetNextWindowPos(ImVec2(0, menu_height));                           
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y-menu_height));


    ImGui::Begin(name, NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("This is a terminal view placeholder.");

    ImGui::End();
}