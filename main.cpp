#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include <allocator/allocator.hpp>
#include <container/container.hpp>

template <int N> struct Factorial
{
    enum
    {
        value = N * Factorial<N - 1>::value
    };
};

template <> struct Factorial<0>
{
    enum
    {
        value = 1
    };
};

int main()
{
    // 1
    std::map<int, int> mp1;
    // 2
    mp1[0] = Factorial<0>::value;
    mp1[1] = Factorial<1>::value;
    mp1[2] = Factorial<2>::value;
    mp1[3] = Factorial<3>::value;
    mp1[4] = Factorial<4>::value;
    mp1[5] = Factorial<5>::value;
    mp1[6] = Factorial<6>::value;
    mp1[7] = Factorial<7>::value;
    mp1[8] = Factorial<8>::value;
    mp1[9] = Factorial<9>::value;
    // 3
    std::map<int, int, std::map<int, int>::key_compare, allocator::CustomAllocator<std::pair<int, int>>> mp2;
    // 4
    mp2[0] = Factorial<0>::value;
    mp2[1] = Factorial<1>::value;
    mp2[2] = Factorial<2>::value;
    mp2[3] = Factorial<3>::value;
    mp2[4] = Factorial<4>::value;
    mp2[5] = Factorial<5>::value;
    mp2[6] = Factorial<6>::value;
    mp2[7] = Factorial<7>::value;
    mp2[8] = Factorial<8>::value;
    mp2[9] = Factorial<9>::value;
    // 5
    for (const auto& [key, val] : mp2)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    // 6
    container::CustomList<int, std::allocator<int>> list{};
    // 7
    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    // 8
    container::CustomList<int, allocator::CustomAllocator<int>> my_list{};
    // 9
    my_list.push_back(0);
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    my_list.push_back(5);
    my_list.push_back(6);
    my_list.push_back(7);
    my_list.push_back(8);
    my_list.push_back(9);
    // 10

    auto* cur = my_list.head();
    while (cur != nullptr)
    {
        std::cout << cur->val << " " << std::endl;
        cur = cur->next;
    }
}