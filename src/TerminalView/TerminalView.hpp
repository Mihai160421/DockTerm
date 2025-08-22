#pragma once


class TerminalView {
private:
    const char* name = "TerminalView";
public:
    TerminalView();
    ~TerminalView() = default;

    void render();
};
