#pragma once
#include "string.h"
#include <cstddef>

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

    CustomList(const CustomList& list)
    {
        m_head = nodeAlloc.allocate(1);
        m_tail = m_head;

        auto curNode = list.m_head;
        while (curNode)
        {
            auto nextNode = curNode->next;
            push_back(curNode->val);
            curNode = nextNode;
        }
    }

    ~CustomList()
    {
        auto curNode = m_head;
        while (curNode)
        {
            auto nextNode = curNode->next;
            nodeAlloc.deallocate(curNode, 1);
            curNode = nextNode;
        }
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

    Node* getNext(Node* node) const
    {
        return node->next;
    }

    bool hasNext(Node* node) const
    {
        return node->next != nullptr;
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
