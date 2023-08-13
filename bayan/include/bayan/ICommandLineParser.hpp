#pragma once

#include <vector>
#include <string>
#include <memory>

namespace byn
{

struct BayanSettings
{
    std::vector<std::string> m_files;
    int block_size;
};

struct ICommandLineParser
{
    virtual BayanSettings Parse(const char ** args, std::size_t cnt) = 0;
};

struct CommandLineParserFactory
{
    static std::unique_ptr<ICommandLineParser> Create();
};

}