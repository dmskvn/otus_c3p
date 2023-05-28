#include <iostream>
#include <sstream>

#include <allocator/allocator.hpp>

int main ()
{

    allocator::CustomAllocator<int, 5> ca{};
    ca.allocate(3);
}