#include <atomic>
#include <memory>
#include <iostream>
#include <thread>
#include <stack>
#include <mutex>

namespace lock_free {

template<typename T>
struct node
{
    std::shared_ptr<T> _data;
    node* _next;
    node(std::shared_ptr<T> data)
        : _data(std::move(data))
        , _next(nullptr) {}
};

template<typename T>
class Stack
{
    std::atomic<node<T>*> _head;

public:

    void push(std::shared_ptr<T> data)
    {
        node<T>* new_node = new node<T>(std::move(data));
        node<T>* old_head = _head.load(std::memory_order_relaxed);

        do
        {
            new_node->_next = old_head;
        }
        while (!_head.compare_exchange_weak(old_head, new_node,
            std::memory_order_release, std::memory_order_relaxed)
        );
    }

    std::shared_ptr<T> pop()
    {
        node<T>* old_head = _head.load(std::memory_order_relaxed);
        node<T>* new_head;

        do {
            if(old_head == nullptr) {
                // need to re-check because every retry reloads old_head
                // pop in another thread might have emptied the list
                return nullptr;
             }

             new_head = old_head->_next;
             // if head still equals old_head this implies the same relation for new_head
         } while(!_head.compare_exchange_weak(old_head, new_head,
            std::memory_order_acquire, std::memory_order_relaxed));
         // Note the ordering change: acquire for both success and failure

         return old_head->_data;  // defer deletion until some later time

    }

};

class StackLFTest
{
    Stack<int> _s;

    void producer(std::size_t i, std::size_t qty)
    {
        for (std::size_t j = i; j < i + qty; ++j)
        {
            //std::cout << "Push " << i << std::endl;
            _s.push(std::make_shared<int>(j));
        }
    }

    void consumer ()
    {

        while(true)
        {
            auto res = _s.pop();
            if (res.get())
            {
                //std::cout << "Pop " << *res << std::endl;
            }
            else
            {
                return;
            }
        }
    }

    public:

    void test()
    {
        std::thread p1(&StackLFTest::producer, this, 0, 100000);
        std::thread p2(&StackLFTest::producer, this, 100000, 100000);
        std::thread p3(&StackLFTest::producer, this, 200000, 100000);
        std::thread p4(&StackLFTest::producer, this, 500000, 100000);
        std::thread p5(&StackLFTest::producer, this, 600000, 100000);
        std::thread p6(&StackLFTest::producer, this, 700000, 100000);

        //std::this_thread::sleep_for(std::chrono::seconds(2));

        std::thread c(&StackLFTest::consumer, this);

        p1.join();
        p2.join();
        p3.join();
        p4.join();
        p5.join();
        p6.join();

        c.join();
    }
};

class StackTest
{
    std::stack<std::shared_ptr<int>> _s;
    std::mutex _m;

    void producer(std::size_t i, std::size_t qty)
    {
        std::lock_guard<std::mutex> l (_m);
        for (std::size_t j = i; j < i + qty; ++j)
        {
            //std::cout << "Push " << i << std::endl;
            _s.push(std::make_shared<int>(j));
        }
    }

    void consumer ()
    {
        std::lock_guard<std::mutex> l (_m);
        while(!_s.empty())
        {
            auto res = _s.top();
            _s.pop();
            if (res.get())
            {
                //std::cout << "Pop " << *res << std::endl;
            }
            else
            {
                return;
            }
        }
    }

    public:

    void test()
    {
        std::thread p1(&StackTest::producer, this, 0, 100000);
        std::thread p2(&StackTest::producer, this, 100000, 100000);
        std::thread p3(&StackTest::producer, this, 200000, 100000);
        std::thread p4(&StackTest::producer, this, 300000, 100000);
        std::thread p5(&StackTest::producer, this, 400000, 100000);
        std::thread p6(&StackTest::producer, this, 500000, 100000);
        //std::this_thread::sleep_for(std::chrono::seconds(2));

        std::thread c(&StackTest::consumer, this);

        p1.join();
        p2.join();
        p3.join();
        p4.join();
        p5.join();
        p6.join();

        c.join();
    }
};

}


