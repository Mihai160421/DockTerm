#pragma once

#include "Cell/Cell.hpp"
#include "ScreenBuffer/ScreenBuffer.hpp"
#include "ScrollBuffer/ScrollBuffer.hpp"

class TerminalView {
private:
    const char* name = "TerminalView";
    ScreenBuffer* screenBuffer = nullptr;
    ScrollBuffer* scrollBuffer = nullptr; 
    bool tDebugWindow = true;

    void renderDebugWindow();

    void RenderScreenBuffer();
    void RenderScrollBuffer();
public:
    TerminalView();
    ~TerminalView() = default;

    void render();
};
