#pragma once

#include <plot/IPlot.hpp>

namespace editor
{
    struct IItem
    {
        virtual void draw(const IPlot& plot) = 0;
    };
}