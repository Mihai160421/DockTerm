#pragma once
#include "imgui.h"

struct Cell {
    char character = ' ';

    ImU32 fgColor = IM_COL32(255, 255, 255, 255); // White
    ImU32 bgColor = IM_COL32(0, 0, 0, 255);
};