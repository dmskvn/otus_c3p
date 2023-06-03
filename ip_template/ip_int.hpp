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
#include <tuple>

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

namespace tuple_helper{

template<typename Tuple, std::size_t I>
struct check_tuple_args_impl
{
    using prev_type = typename std::tuple_element<I, Tuple>::type;
    using curr_type = typename std::tuple_element<I - 1, Tuple>::type;
    static_assert(std::is_same<prev_type, curr_type>::value, "Check template parameter");
    check_tuple_args_impl <Tuple, I - 1> _t;
};

template<typename Tuple>
struct check_tuple_args_impl <Tuple, 0>
{
    using prev_type = typename std::tuple_element<1, Tuple>::type;
    using curr_type = typename std::tuple_element<0, Tuple>::type;
    static_assert(std::is_same<prev_type, curr_type>::value, "Check template parameter");
};

template<typename Tuple>
constexpr void check_tuple()
{
    check_tuple_args_impl <Tuple, std::tuple_size<Tuple>::value - 1> check;
}

template <std::size_t I, std::size_t J, typename ...Args>
struct PrintImpl
{
void print (const std::tuple<Args...>& tuple, bool printDot = false)
{
   std::cout << std::get<I>(tuple);
   if (printDot)
   {
       std::cout << ".";
       PrintImpl<I+1, J - 1, Args...> print;
       print.print(tuple, true);
   }
   else
   {
       std::cout << std::endl;
   }
}
};

template <std::size_t I,  typename ...Args>
struct PrintImpl<I, 0, Args...>
{
    void print (const std::tuple<Args...>& tuple, bool printDot = false)
    {
        std::cout << std::get<I>(tuple) << std::endl;
    }
};

}


template <typename ...Args>
void print(const std::tuple<Args...>& tuple)
{
    using tuple_type = std::tuple <Args...>;
    tuple_helper::check_tuple<std::tuple<Args...>>();
    tuple_helper::PrintImpl<0, std::tuple_size<tuple_type>::value - 1, Args...> t;
    t.print(tuple, true);
}


int main()
{
    std::vector <int32_t> d {1,2,3,4,5};
    //print (d);
    int j = 2130706433;
    //print(j);
    std::tuple <int, int,int> t {1,2,3};
    print (t);
}
