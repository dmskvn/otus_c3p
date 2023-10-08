#pragma once

#include <future>
#include <iostream>

namespace lock_free {


    class MotivationExplanation
    {
        int _a = 0;
        int _b = 0;
        int _c = 0;

        int _s = 0;

        void producer()
        {
            int random = 1 + (rand() % 3);

            if (random == 1)
            {
                _a = 10;
                _b = 11;
                _c = 12;
                _s = 1;
                return;
            }

            if (random == 2)
            {
                _a = 20;
                _b = 21;
                _c = 22;
                _s = 2;
                return;
            }

            if (random == 3)
            {
                _a = 30;
                _b = 31;
                _c = 32;
                _s = 3;
                return;
            }

        };


        void consumer()
        {
            while (_s == 0)
            {
            }

            if (_s == 1)
            {
                if (_a != 10 || _b != 11 || _c != 12)
                {
                    std::cout << "cpu was broken _a" << std::endl;
                    return;
                }
            }

            if (_s == 2)
            {
                if (_a != 20 || _b != 21 || _c != 22)
                {
                    std::cout << "cpu was broken _b" << std::endl;
                    return;
                }
            }

            if (_s == 3)
            {
                if (_a != 30 || _b != 31 || _c != 32)
                {
                    std::cout << "cpu was broken _c" << std::endl;
                    return;
                }
            }

        }


    public:
        void test(int j)
        {
            for (int i = 0; i < j; ++i)
            {
                std::thread producer (&MotivationExplanation::producer, this);
                std::thread consumer (&MotivationExplanation::consumer, this);

                producer.join();
                consumer.join();

//                if (i % 1000 == 0)
//                {
//                    std::cout << "--- " << i << " ---" << std::endl;
//                }

                _s = 0;
            }
        }
    };


    class RelaxedExplanation
    {
        int _a = 0;
        int _b = 0;
        int _c = 0;

        std::atomic<int> _s;

        void producer()
        {
            int random = 1 + (rand() % 3);

            if (random == 1)
            {
                _a = 10;
                _b = 11;
                _c = 12;
                _s.store(1, std::memory_order_relaxed);
                return;
            }

            if (random == 2)
            {
                _a = 20;
                _b = 21;
                _c = 22;
                _s.store(2, std::memory_order_relaxed);
                return;
            }

            if (random == 3)
            {
                _a = 30;
                _b = 31;
                _c = 32;
                _s.store(3, std::memory_order_relaxed);
                return;
            }

        };


        void consumer()
        {
            int s = 0;
            while (!s)
            {
                s = _s.load(std::memory_order_relaxed);
            }

            if (s == 1)
            {
                if (_a != 10 || _b != 11 || _c != 12)
                {
                    std::cout << "cpu was broken _a" << std::endl;
                    return;
                }
            }

            if (s == 2)
            {
                if (_a != 20 || _b != 21 || _c != 22)
                {
                    std::cout << "cpu was broken _b" << std::endl;
                    return;
                }
            }

            if (s == 3)
            {
                if (_a != 30 || _b != 31 || _c != 32)
                {
                    std::cout << "cpu was broken _c" << std::endl;
                    return;
                }
            }

        }


    public:
        void test(int j)
        {
            for (int i = 0; i < j; ++i)
            {
                _s = 0;

                auto fp = std::async(std::launch::async, &RelaxedExplanation::producer, this);
                auto fc = std::async(std::launch::async, &RelaxedExplanation::consumer, this);

                fp.get();
                fc.get();

//                if (i % 1000 == 0)
//                {
//                    std::cout << "--- " << i << " ---" << std::endl;
//                }
            }
        }
    };


    class AquireReleaseExplanation
    {
        int _a = 0;
        int _b = 0;
        int _c = 0;

        std::atomic<int> _s;

        void producer()
        {
            int random = 1 + (rand() % 3);

            if (random == 1)
            {
                _a = 10;
                _b = 11;
                _c = 12;
                _s.store(1, std::memory_order_release);
                return;
            }

            if (random == 2)
            {
                _a = 20;
                _b = 21;
                _c = 22;
                _s.store(2, std::memory_order_release);
                return;
            }

            if (random == 3)
            {
                _a = 30;
                _b = 31;
                _c = 32;
                _s.store(3, std::memory_order_release);
                return;
            }

        };


        void consumer()
        {
            int s = 0;
            while (!s)
            {
                s = _s.load(std::memory_order_acquire);
            }

            if (s == 1)
            {
                if (_a != 10 || _b != 11 || _c != 12)
                {
                    std::cout << "cpu was broken _a" << std::endl;
                    return;
                }
            }

            if (s == 2)
            {
                if (_a != 20 || _b != 21 || _c != 22)
                {
                    std::cout << "cpu was broken _b" << std::endl;
                    return;
                }
            }

            if (s == 3)
            {
                if (_a != 30 || _b != 31 || _c != 32)
                {
                    std::cout << "cpu was broken _c" << std::endl;
                    return;
                }
            }

        }


    public:
        void test(int j)
        {
            for (int i = 0; i < j; ++i)
            {
                _s = 0;

                auto fp = std::async(std::launch::async, &AquireReleaseExplanation::producer, this);
                auto fc = std::async(std::launch::async, &AquireReleaseExplanation::consumer, this);

                fp.get();
                fc.get();

//                if (i % 1000 == 0)
//                {
//                    std::cout << "--- " << i << " ---" << std::endl;
//                }
            }
        }
    };



    class CounterMutex
    {
        std::mutex _m;
        int _ctr = 0;

    public:

        void inc()
        {
            _m.lock();
            ++_ctr;
            _m.unlock();
        }

        void test(int j)
        {
            std::vector<std::thread> thrds;
            for (int i = 0; i < j; ++i)
            {
                thrds.push_back(std::thread(&CounterMutex::inc, this));
            }

            for (int i = 0; i < j; ++i)
            {
                thrds[i].join();
            }
        }
    };

    class SeqCstCounter
    {
        std::atomic<int> _ctr;

    public:

        void inc()
        {
            ++_ctr;
        }

        void test(int j)
        {
            _ctr = 0;
            std::vector<std::thread> thrds;
            for (int i = 0; i < j; ++i)
            {
                thrds.push_back(std::thread(&SeqCstCounter::inc, this));
            }

            for (int i = 0; i < j; ++i)
            {
                thrds[i].join();
            }
        }
    };

    class RelaxedCounter
    {
        std::atomic<int> _ctr;

    public:

        void inc()
        {
            _ctr.fetch_add(1, std::memory_order_relaxed);
        }

        void test(int j)
        {
            _ctr = 0;
            std::vector<std::thread> thrds;
            for (int i = 0; i < j; ++i)
            {
                thrds.push_back(std::thread(&RelaxedCounter::inc, this));
            }

            for (int i = 0; i < j; ++i)
            {
                thrds[i].join();
            }
        }
    };





}
