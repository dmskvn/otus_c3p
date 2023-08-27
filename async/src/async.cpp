
#include "async/async.h"
#include "Writer.hpp"

namespace async
{
    static Processor prc;

    int connect(std::size_t block_size){
        auto ret = prc.connect(block_size);
        return ret;
    }

    void receive(int handle, const char* buf, std::size_t buf_size){
        prc.receive(handle, buf, buf_size);
    }

    void disconnect(int handle)
    {
        prc.disconnect(handle);
    }
}
