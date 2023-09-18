#pragma once

#include <atomic>
#include <vector>
#include <thread>

namespace lock_free
{

struct BadSpinLockMtx {

  std::atomic<bool> lock_ = {false};

  void lock() { while(lock_.exchange(true)); }

  void unlock() { lock_.store(false); }
};


struct BetterSpinLockMtx {

  std::atomic<bool> lock_ = {false};

  void lock() { while(lock_.exchange(true, std::memory_order_acquire)); }

  void unlock() { lock_.store(false, std::memory_order_release); }

};

struct BestSpinLockMtx {

  std::atomic<bool> lock_ = {false};

  void lock() {
    for (;;) {
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        break;
      }
      while (lock_.load(std::memory_order_relaxed)) {
        __builtin_ia32_pause();
      }
    }
  }

  void unlock() { lock_.store(false, std::memory_order_release); }

};


template <typename Lock>
class Test{

    Lock lk;

    void thread()
    {
        lk.lock();

        std::vector<int> data;
        data.push_back(1);
        data.push_back(2);
        for (int i = 0; i < 1000; ++i)
        {
            data.push_back(data.back() + *(data.end() - 2));
        }

        lk.unlock();
    }



public:

    Test (std::size_t threads_qty)
    {
        std::vector<std::thread> threads;

        for (std::size_t i = 0; i < threads_qty; ++i)
        {
            threads.push_back(std::thread(&Test::thread, this));
        }

        for (std::size_t i = 0; i < threads_qty; ++i)
        {
            threads[i].join();
        }
    }
};

}
