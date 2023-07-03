#pragma once

#include <unordered_map>

template <typename T, T dflt>
class Matrix
{
    std::unordered_map <std::pair<std::size_t, std::size_t>, T> _elems;

    public:

    const T& get_element (const std::size_t x, const std::size_t y) const
    {
        if (!_elems.count())
        {
            return dflt;
        }
        else
        {
            return _elems[{x, y}];
        }
    }
};

