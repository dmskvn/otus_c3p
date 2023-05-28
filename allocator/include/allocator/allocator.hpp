#pragma once
#include <array>
#include <exception>
#include <iostream>
#include <limits>
#include <memory>

namespace allocator
{

template <class T> struct CustomAllocator
{
    using value_type = T;

  private:

    static constexpr std::size_t CHUNK_SIZE = 20;
    static constexpr std::size_t PAGES_QTY = 3;

    struct MemoryPage
    {
        std::size_t free = CHUNK_SIZE;
        std::size_t tail = 0;
        std::array<char, sizeof(T) * CHUNK_SIZE> memory;
    };

    std::array<MemoryPage, PAGES_QTY> pages;

  public:

    CustomAllocator() noexcept
    {
    }

    T* allocate(std::size_t n)
    {
        const auto optimum_page = find_optimum_page_to_allocate(n);
        const auto result = reinterpret_cast<T*>(&pages[optimum_page].memory) + pages[optimum_page].tail;
        pages[optimum_page].tail += n;
        pages[optimum_page].free -= n;
        return result;
    }

    void deallocate(T* p, std::size_t n)
    {
        const auto page_num = find_page_num_by_addr(p);
        pages[page_num].free += n;
        if (pages[page_num].free == CHUNK_SIZE)
        {
            pages[page_num].tail = 0;
        }
    }

    template <class U> struct rebind
    {
        typedef CustomAllocator<U> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

    std::size_t find_optimum_page_to_allocate(const std::size_t to_alloc)
    {
        auto optimal_page = pages.size();
        auto optimal_free = std::numeric_limits<std::size_t>::max();

        for (std::size_t i = 0; i < pages.size(); ++i)
        {
            if (to_alloc == pages[i].free)
            {
                optimal_page = i;
                optimal_free = pages[i].free;
                break;
            }
            else if (to_alloc < pages[i].free && optimal_free > pages[i].free)
            {
                optimal_page = i;
                optimal_free = pages[i].free;
            }
        }

        if (optimal_page == pages.size())
        {
            throw std::bad_alloc();
        }

        return optimal_page;
    }

    std::size_t find_page_num_by_addr(const T* addr)
    {
        for (std::size_t i = 0; i < pages.size(); ++i)
        {
            if (pages[i].tail == 0)
            {
                continue;
            }
            const auto first_chunk_of_page = reinterpret_cast<T*>(&pages[i].memory[0]);
            const auto last_chunk_of_page = reinterpret_cast<T*>(&pages[i].memory[pages[i].memory.size() - 1]);
            if (addr >= first_chunk_of_page && addr <= last_chunk_of_page)
            {
                return i;
            }
        }
        throw std::bad_alloc();
    }
};
template <class T, class U>
constexpr bool operator==(const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept
{
    return a1.pool == a2.pool;
}

template <class T, class U>
constexpr bool operator!=(const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept
{
    return a1.pool != a2.pool;
}

} // namespace allocator
