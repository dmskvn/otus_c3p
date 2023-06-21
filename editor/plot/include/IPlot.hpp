#pragma once

#include <cstdint>

namespace editor
{
    struct IPlot
    {
        virtual void draw_point (const uint64_t x, const uint64_t y, const uint64_t colour) = 0;
    };
}