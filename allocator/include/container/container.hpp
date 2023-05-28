#pragma once
#include "string.h"

namespace container
{
template <typename T, typename Alloc> class CustomList
{
    struct Node
    {
        Node* next = nullptr;
        T val;
    };

  public:

    CustomList()
    {
        m_head = nodeAlloc.allocate(1);
        m_tail = m_head;
    }

    void push_back(const T& val)
    {
        m_tail->next = nodeAlloc.allocate(1);
        memcpy(static_cast<void*>(&m_tail->next->val), static_cast<const void*>(&val), sizeof(T));
        m_tail = m_tail->next;
        ++m_size;
    }

    Node* head() const
    {
        return m_head;
    }

    std::size_t size() const
    {
        return m_size;
    }

    std::size_t empty() const
    {
        return m_size == 0;
    }

  private:

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    std::size_t m_size = 0;
    typename Alloc::template rebind<Node>::other nodeAlloc;
};

} // namespace container