#pragma once

#include <future>
#include <iostream>

namespace lock_free {

class Motivation
{
    int m_a = 0;
    int m_b = 0;
    int m_c = 0;
    int m_d = 0;
    int m_e = 0;

    int m_is_ready;

    int m_counter = 0;

    int m_max_counter = 0;

    void producer ()
    {
        m_a = 1;
        m_b = 2;
        m_c = 3;
        m_d = 4;
        m_e = 5;

        m_is_ready = true;
    }

    void consumer ()
    {
        while (!m_is_ready) {}

        m_is_ready = false;

        m_counter++;
        //std::cout << m_counter++ << std::endl;
        if (m_a != 1 || m_b != 2 || m_c != 3 || m_d != 4 || m_e != 5)
        {
            std::cout << "YOUR PC IS BROKEN! m_a:" << m_a
                << " m_b:" << m_b
                << " m_c:" << m_c
                << " m_d:" << m_d
                << " m_e:" << m_e
                << " m_counter:" << m_counter
                << std::endl;
        }

        //std::cout << "ok" << std::endl;

        if (m_max_counter == m_counter) return;

        m_a = 0;
        m_b = 0;
        m_c = 0;
        m_d = 0;
        m_e = 0;
    }


public:

    Motivation(int max_counter)
        :m_max_counter(max_counter)
    {}

    void start_test()
    {

        while (true) {

            m_is_ready = false;

            //auto future_producer = std::async(std::launch::async, &Motivation::producer, this);
            //auto future_consumer = std::async(std::launch::async, &Motivation::consumer, this);

            //future_producer.wait();

            //auto test_failed = future_consumer.get();
            //clear();

            std::thread producer (&Motivation::producer, this);
            std::thread consumer (&Motivation::consumer,this);

            producer.join();
            consumer.join();

            if (m_max_counter == m_counter) return;
        }
    }

};


    class AtomicMotivation
    {

        std::memory_order m_load_mo;
        std::memory_order m_store_mo;

        int m_a = 0;
        int m_b = 0;
        int m_c = 0;
        int m_d = 0;
        int m_e = 0;

        std::atomic<bool> m_is_ready;

        int m_counter = 0;

        int m_max_counter = 0;

        void producer ()
        {
            m_a = 1;
            m_b = 2;
            m_c = 3;
            m_d = 4;
            m_e = 5;

            m_is_ready.store(true, m_store_mo);
        }

        void consumer ()
        {
            while (!m_is_ready.load(m_load_mo)) {}

            m_is_ready = false;

            m_counter++;
            //std::cout << m_counter++ << std::endl;
            if (m_a != 1 || m_b != 2 || m_c != 3 || m_d != 4 || m_e != 5)
            {
                std::cout << "YOUR PC IS BROKEN! m_a:" << m_a
                    << " m_b:" << m_b
                    << " m_c:" << m_c
                    << " m_d:" << m_d
                    << " m_e:" << m_e
                    << " m_counter:" << m_counter
                    << std::endl;
            }

            //std::cout << "ok" << std::endl;

            m_a = 0;
            m_b = 0;
            m_c = 0;
            m_d = 0;
            m_e = 0;

            m_is_ready.store(false, m_store_mo);
        }


    public:

        AtomicMotivation(std::memory_order load_mo, std::memory_order store_mo, int max_counter)
            :m_load_mo(load_mo)
            ,m_store_mo(store_mo)
            ,m_max_counter(max_counter)
        {}

        void start_test()
        {

            while (true) {

                m_is_ready = false;

                //auto future_producer = std::async(std::launch::async, &Motivation::producer, this);
                //auto future_consumer = std::async(std::launch::async, &Motivation::consumer, this);

                //future_producer.wait();

                //auto test_failed = future_consumer.get();
                //clear();

                std::thread producer (&AtomicMotivation::producer, this);
                std::thread consumer (&AtomicMotivation::consumer, this);

                producer.join();
                consumer.join();

                if (m_max_counter == m_counter) return;
            }
        }
    };

}
