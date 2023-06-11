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
#include <list>

#include <tuple>

namespace ip_template {

struct TypeIsStdContainer{};
struct TypeIsInt{};
struct TypeIsStdString{};

template <typename T, typename F=void>
struct TypeSelector
{};

/**
 * @brief SFINAE selector for vector
 * 
 * @tparam T 
 */
template <typename T>
struct TypeSelector<std::vector<T>> {using type = TypeIsStdContainer;};

/**
 * @brief SFINAE selector for set container
 * 
 * @tparam T 
 */
template <typename T>
struct TypeSelector<std::set<T>> {using type = TypeIsStdContainer;};

/**
 * @brief SFINAE selector for list container
 * 
 * @tparam T 
 */
template <typename T>
struct TypeSelector<std::list<T>> {using type = TypeIsStdContainer;};


/**
 * @brief SFINAE selector for string container
 * 
 * @tparam T 
 */
template <>
struct TypeSelector<std::string> {using type = TypeIsStdString;};

/**
 * @brief SFINAE selector for int
 * 
 * @tparam T 
 */
template<typename T>
struct TypeSelector<T, typename std::enable_if<std::is_arithmetic<T>::value>::type>{using type = TypeIsInt;};

/**
 * @brief Prints ip represented as int variable 
 * 
 * @tparam T Int type
 * @param val Int value
 * @param printDot Prints dot after int
 * @return std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsInt>::value, void>::type 
 */
template <typename T>
typename std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsInt>::value, void>::type
print (const T& val)
{
    auto to_print = val;
    for (std::size_t i = 0; i < sizeof (T); ++i)
    {
        to_print = (val >> 8*(sizeof (T) - 1 - i));
        std::cout << uint(to_print & 0xFF);
        if (i != sizeof (T) - 1)
        {
            std::cout << ".";
        }
        else
        {
            std::cout << std::endl;
        }
    }
}

/**
 * @brief Prints string elements
 *
 * @tparam string
 */
template <typename T>
typename std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsStdString>::value, void>::type
print (const T& string)
{
    for (const auto& c : string)
    {
        std::cout << c;
    }
    std::cout << std::endl;
}

/**
 * @brief Prints container elements
 * 
 * @tparam container 
 */
template <typename T>
typename std::enable_if<std::is_same<typename TypeSelector<T>::type, TypeIsStdContainer>::value, void>::type
print (const T& container)
{
    for (auto it = container.begin(); it != container.cend(); ++it)
    {
        std::cout << *it;
        if (std::next(it) != container.end())
        {
            std::cout<< ".";
        }
        else
        {
            std::cout << std::endl;
        }
    }
}

namespace tuple_helper{

/**
 * @brief Check if all tuple types are equal otherwise call compile-time exception
 * 
 * @tparam Tuple 
 */
template<typename Tuple, std::size_t I>
struct check_tuple_args_impl
{
    using prev_type = typename std::tuple_element<I, Tuple>::type;
    using curr_type = typename std::tuple_element<I - 1, Tuple>::type;
    static_assert(std::is_same<prev_type, curr_type>::value, "Check template parameter");
    check_tuple_args_impl <Tuple, I - 1> _t;
};

/**
 * @brief Check if pre-last and last tuple types are equal otherwise call compile-time exception
 * 
 * @tparam Tuple 
 */
template<typename Tuple>
struct check_tuple_args_impl <Tuple, 0>
{
    using prev_type = typename std::tuple_element<1, Tuple>::type;
    using curr_type = typename std::tuple_element<0, Tuple>::type;
    static_assert(std::is_same<prev_type, curr_type>::value, "Check template parameter");
};

/**
 * @brief Check if there all template arguments are equal otherwise call compile-time exception
 * 
 * @tparam Tuple 
 */
template<typename Tuple>
constexpr void check_tuple()
{
    [[maybe_unused]] check_tuple_args_impl <Tuple, std::tuple_size<Tuple>::value - 1> check;
}

/**
 * @brief This function prints all elements of template
 * 
 * @tparam I Increasing index
 * @tparam J Decreasing index
 * @tparam Args Parameters pack of tuple
 */
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

/**
 * @brief This function prints last element of template
 * 
 * @tparam Args 
 * @param tuple template to print
 */
template <std::size_t I,  typename ...Args>
struct PrintImpl<I, 0, Args...>
{
    void print (const std::tuple<Args...>& tuple, [[maybe_unused]] bool printDot)
    {
        std::cout << std::get<I>(tuple) << std::endl;
    }
};

}

/**
 * @brief This function prints all template members if their types are equal
 * 
 * @tparam Args 
 * @param tuple template to print
 */
template <typename ...Args>
void print(const std::tuple<Args...>& tuple)
{
    using tuple_type = std::tuple <Args...>;
    tuple_helper::check_tuple<std::tuple<Args...>>();
    tuple_helper::PrintImpl<0, std::tuple_size<tuple_type>::value - 1, Args...> t;
    t.print(tuple, true);
}

}
