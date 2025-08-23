#include "ScrollBuffer.hpp"

ScrollBuffer::ScrollBuffer()
{
}
ScrollBuffer::~ScrollBuffer()
{
}

void ScrollBuffer::PushRow(const std::vector<Cell>& row)
{
    buffer.push_back(row);

    // TODO: Implement a maximum size for the scroll buffer
    if (buffer.size() > 1000) // Limit buffer size to last 1000 rows
        buffer.pop_front();
}

void ScrollBuffer::Render(int startRow, int numRows)
{
    int endRow = std::min(startRow + numRows, static_cast<int>(buffer.size()));
    for (int r = startRow; r < endRow; ++r)
    {
        const auto& row = buffer[r];
        for (const auto& cell : row)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, cell.fgColor);
            ImGui::TextUnformatted(&cell.character, &cell.character + 1);
            ImGui::PopStyleColor();
            ImGui::SameLine(0.0f, 0.0f); // No spacing between characters
        }
        ImGui::NewLine();
    }
}
