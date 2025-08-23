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

private:
    std::vector<Cell> buffer;
    int width = 0;
    int height = 0; 
};
