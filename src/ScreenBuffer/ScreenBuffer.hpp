#pragma once

#include <vector>

#include "Cell/Cell.hpp"

class ScreenBuffer {
public:
    ScreenBuffer(int w, int h) : width(w), height(h), buffer(w * h) {};
    ~ScreenBuffer() = default;

    void resize(int new_w, int new_h);
    Cell& at(int r, int c);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    int GetcursorX() const { return static_cast<int>(cursor.x); }
    int GetcursorY() const { return static_cast<int>(cursor.y); }
    ImVec2 Getcursor() const { return cursor; }

private:
    std::vector<Cell> buffer;
    int width = 0;
    int height = 0; 

    ImVec2 cursor = ImVec2(0, 0);
};
