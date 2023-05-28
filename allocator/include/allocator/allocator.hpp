#pragma once
#include <array>
#include <exception>
#include <limits>
#include <memory>

namespace allocator
{

template <class T, unsigned int N = 5> struct CustomAllocator
{
    using value_type = T;

  private:

    struct MemoryPage
    {
        std::size_t free = N;
        std::size_t tail = 0;
        std::array<char, sizeof(T) * N> memory;
    };

    std::array<MemoryPage, 3> pages;

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
        if (pages[page_num].free == N)
        {
            pages[page_num].tail = 0;
        }
    }

    // template <class U> struct rebind
    // {
    //     typedef cpp_11_allocator<U> other;
    // };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; // UB if std::false_type and a1 != a2;

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
            const auto first_chunk_of_page = static_cast<T*>(&pages[i].memory());
            const auto last_chunk_of_page = static_cast<T*>(&pages[pages.size() - 1].memory());
            if (addr >= first_chunk_of_page && addr <= last_chunk_of_page)
            {
                return i;
            }
        }
        throw std::bad_alloc();
    }
};

} // namespace allocator
