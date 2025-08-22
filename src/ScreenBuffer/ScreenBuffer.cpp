#include "ScreenBuffer.hpp"

void ScreenBuffer::resize(int new_w, int new_h)
{
    std::vector<Cell> new_buff(new_w * new_h);

    int copy_w = std::min(new_w, this->width);
    int copy_h = std::min(new_h, this->height);

    for (int r = 0; r < copy_h; ++r)
        for (int c = 0; c < copy_w; ++c)
            new_buff[r * new_w + c] = at(r, c);

    this->width = new_w;
    this->height = new_h;
    this->buffer = std::move(new_buff);
}

Cell &ScreenBuffer::at(int r, int c)
{
    return buffer[r * width + c];
}
