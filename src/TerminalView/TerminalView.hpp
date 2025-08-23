#pragma once

#include "Cell/Cell.hpp"
#include "ScreenBuffer/ScreenBuffer.hpp"

class TerminalView {
private:
    const char* name = "TerminalView";
    ScreenBuffer* screenBuffer = nullptr;
    bool tDebugWindow = true;

    void renderDebugWindow();

    void RenderScreenBuffer();

public:
    TerminalView();
    ~TerminalView() = default;

    void render();
};
