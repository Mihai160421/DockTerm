#pragma once

#include <deque>
#include <vector>
#include "Cell/Cell.hpp"


class ScrollBuffer
{
private:
    std::deque<std::vector<Cell>> buffer;
public:
    ScrollBuffer() = default;
    ~ScrollBuffer() = default;

    void PushRow(const std::vector<Cell>& row);
    void Clear() { buffer.clear(); }
    int GetRowsCount() const { return static_cast<int>(buffer.size()); }

    void Render(int startRow, int numRows);
};
