#include <memory>
#include <vector>
#include <mutex>
#include <ostream>
#include <queue>
#include <future>
#include <optional>
#include <iostream>
#include <fstream>
#include <map>
#include <cmd/ICommandFactory.hpp>

namespace async
{

    struct IMTWriter
    {
        virtual void write(const std::string data) = 0;
        virtual void stop() = 0;
        virtual ~IMTWriter() = default;
    };

    struct IMTWriterFactory
    {
        virtual std::unique_ptr<IMTWriter> create(std::string type, std::size_t threads) = 0;
        virtual ~IMTWriterFactory() = default;
    };

    struct ISink
    {
        virtual void write(const std::string& data) = 0;
        virtual ~ISink() = default;
    };

    struct CoutWriter : ISink
    {
        void write (const std::string& data)
        {
            std::cout << data << std::endl;
        }
    };

    struct FileWriter : ISink
    {
        std::string m_prefix;
        std::atomic<int> cnt{0};
        std::fstream _file;

        FileWriter(std::string prefix)
            : m_prefix(std::move(prefix))
        {
        }

        void write(const std::string& data)
        {
            const auto file_name = m_prefix + std::to_string(cnt);

            _file.open(file_name, std::fstream::out);
            _file.write(data.c_str(), data.size());
            _file.flush();
            _file.close();
        }
    };

    struct ISinkFactory
    {
        virtual std::unique_ptr<ISink> create() = 0;
        virtual ~ISinkFactory() = default;
    };
    
    struct ConsoleSinkFactory : public ISinkFactory
    {
        virtual std::unique_ptr<ISink> create() override
        {
            return std::make_unique<CoutWriter>();
        }
    };

    struct FileOutputSinkFactory : public ISinkFactory
    {
        std::atomic<int> cnt{0};

        virtual std::unique_ptr<ISink> create() override
        {
            ++cnt;
            return std::make_unique<FileWriter>(std::to_string(cnt) + "_file");
        }
    };

    struct BaseMTWriter : IMTWriter
    {

        std::unique_ptr<ISink> m_sink;

        std::atomic<bool> m_stop;
        std::queue<std::string> m_pending;
        std::mutex m_mtx;

        std::unique_ptr<std::thread> m_thread;

        BaseMTWriter(std::unique_ptr<ISink> sink)
            :m_sink(std::move(sink))
            ,m_stop(false)
        {
            m_thread = std::make_unique<std::thread>(&BaseMTWriter::task, this);
        }

        void task()
        {
            while(m_stop.load(std::memory_order_relaxed))
            {
                std::lock_guard <std::mutex> lg(m_mtx);
                if (m_pending.empty()) continue;
                m_sink->write(m_pending.front());
                m_pending.pop();
            }
        }

        virtual void write(std::string data) override
        {
            std::lock_guard <std::mutex> lg(m_mtx);
            m_pending.push(data);
        }

        virtual void stop() override
        {
            m_stop.store(true, std::memory_order_relaxed);
            while (m_pending.empty())
            {}
        }
    };

    struct Processor
    {
        int handle = 1;
        std::map<int, std::unique_ptr<cmd::ICommandStorage>> m_cmd_strgs;
        std::map<int, std::size_t> m_block_size;

        std::unique_ptr<BaseMTWriter> m_cout;
        std::unique_ptr<BaseMTWriter> m_log1;
        std::unique_ptr<BaseMTWriter> m_log2;

        Processor()
            :m_cout(std::make_unique<BaseMTWriter>(std::make_unique<CoutWriter>()))
            ,m_log1(std::make_unique<BaseMTWriter>(std::make_unique<FileWriter>("log1_")))
            ,m_log2(std::make_unique<BaseMTWriter>(std::make_unique<FileWriter>("log2_")))
        {}

        int connect(std::size_t block_size)
        {
            m_cmd_strgs[handle]= cmd::CreateStorage();
            m_block_size[handle]=block_size;
            ++handle;
            return handle - 1;
        }

        void receive(int handle, const char* data, std::size_t data_size)
        {
            auto cmd = cmd::CreateCommandFactory(m_block_size[handle])->Create(std::string(data, data_size));
            auto pkg = cmd->execute(*m_cmd_strgs[handle].get());

            if (!pkg.empty())
            {
                auto line = std::string{};

                for (const auto& p : pkg)
                {
                    line += p + " ";
                }

                m_cout->write(line);
                if (!(handle % 2))
                {
                    m_log1->write(line);
                }
                else
                {
                    m_log2->write(line);
                }

            }
        }

        void prc_flush()
        {
            m_cout->stop();
            m_log1->stop();
            m_log2->stop();
        }

        void disconnect(int handle)
        {
            m_cmd_strgs.erase(handle);
            m_block_size.erase(handle);

            if (m_block_size.empty())
            {
                prc_flush();
            }
        }


    };

    static Processor prc;

    int connect(std::size_t block_size)
    {
        return prc.connect(block_size);
    }

    void receive(int handle, const char* buf, std::size_t buf_size)
    {
        prc.receive(handle, buf, buf_size);
    }

    void disconnect(int handle)
    {
        prc.disconnect(handle);
    }

}

