#include <iostream>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>


struct TypeIsContainer{};
struct TypeIsInt{};

template <typename T, typename F=void>
struct TypeSelector
{};

template <typename T>
struct TypeSelector<std::vector<T>> {using type = TypeIsContainer;};

template <typename T>
struct TypeSelector<std::set<T>> {using type = TypeIsContainer;};


template<typename T>
struct TypeSelector<T, typename std::enable_if<std::is_arithmetic<T>::value>::type>{using type = TypeIsInt;};

template <typename T>
typename std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsInt>::value, void>::type
print (const T& val, bool printDot = false)
{
    if (!val) return;
    print(val / 10, true);
    std::cout << val % 10;
    if (printDot)
    {
        std::cout << ".";
    }
    else
    {
        std::cout << std::endl;
    }
}

template <typename T>
typename std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsContainer>::value, void>::type
print (const T& container)
{
    std::for_each (container.cbegin(),
        container.cend() - 1,
        [](const auto& val){std::cout << val << ".";}
    );
    std::cout << *(container.cend() - 1) << std::endl;
}   



int main()
{
    std::vector <int32_t> d {1,2,3,4,5};
    print (d);
    int j = 2130706433;
    print(j);
}