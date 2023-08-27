#pragma once

#include <cstddef>

namespace async
{
    int connect(std::size_t frame);

    void receive(int handle, const char* buf, std::size_t buf_size);

    void desconnect(int handle);

    void flush();
}
