#include <iostream>
#include <type_traits>

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

// template <typename T>
// struct TypeSelector<std::vector<T>> {using type = TypeIsVector;};



template<typename T>
struct TypeSelector<T, typename std::enable_if<std::is_arithmetic<T>::value>::type>{using type = TypeIsInt;};

template <typename T>
typename std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsInt>::value, void>::type
print (const T&)
{
    std::cout << "print int" << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsContainer>::value, void>::type
print (const T&)
{
    std::cout << "print container" << std::endl;
}


int main()
{
    std::vector <int> d {1,2,3,4,5};
    print (d);
    int j = 9;
    print(j);
}