#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <chrono>

#include <lock_free/Motivation.hpp>
#include <lock_free/SpinLockMtx.hpp>
#include <lock_free/Stack.hpp>

#include <chrono>

int main() {

    {
        auto begin = std::chrono::system_clock::now();
        lock_free::MotivationExplanation motivation;
        motivation.test(20000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Motivation:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::AquireReleaseExplanation motivation;
        motivation.test(20000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Motivation aquire release:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::RelaxedExplanation motivation;
        motivation.test(20000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Motivation relaxed:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }

    // -----------------------------
    // -----------------------------
    // -----------------------------

    {
        auto begin = std::chrono::system_clock::now();
        lock_free::SeqCstCounter motivation;
        motivation.test(20000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Counter seqcst:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::CounterMutex motivation;
        motivation.test(20000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Counter mutex:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::RelaxedCounter motivation;
        motivation.test(20000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Counter relaxed:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }

    // -----------------------------
    // -----------------------------
    // -----------------------------

    {
        auto begin = std::chrono::system_clock::now();
        lock_free::StackLFTest test;
        test.test();
         auto end = std::chrono::system_clock::now();
         std::cerr << "LockFreeStack Test: " <<  std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::StackTest test;
        test.test();
        auto end = std::chrono::system_clock::now();
        std::cerr << "Stack Test: " <<  std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }


    // -----------------------------
    // -----------------------------
    // -----------------------------

    {
        auto begin = std::chrono::system_clock::now();
        lock_free::Test<std::mutex> t (10000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Stack Mtx lock: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::Test<lock_free::BadSpinLockMtx> t (10000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Bad spin lock: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::Test<lock_free::BetterSpinLockMtx> t (10000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Better spin lock: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }
    {
        auto begin = std::chrono::system_clock::now();
        lock_free::Test<lock_free::BestSpinLockMtx> t (10000);
        auto end = std::chrono::system_clock::now();
        std::cout << "Best spin lock: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }

}
