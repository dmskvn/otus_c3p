#include "bayan/ICommandLineParser.hpp"

#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>
#include <exception>
#include <filesystem>

namespace po = boost::program_options;

namespace byn
{

struct CommandLineParser : ICommandLineParser
{
    virtual BayanSettings Parse(const char ** args, std::size_t cnt) override
    {
        try
        {
            po::options_description desc("Allowed options");
            desc.add_options()
                ("help", "produce help message")
                ("input", po::value<std::string>()->multitoken())
                ("block_size", po::value<int>(), "block size");

            po::parsed_options parsed_options = po::command_line_parser(cnt, args)
                .options(desc).run();
            
            std::vector<std::string> directories;
            std::string block_size;

            for (const po::option& o : parsed_options.options)
            {
                if (o.string_key == "input") directories.push_back(*o.value.cbegin());
                if (o.string_key == "block_size") block_size = *o.value.cbegin();
            }

            std::vector<std::string> files;

            for (const auto& directory : directories)
            {
                for (const auto& file : std::filesystem::directory_iterator(directory))
                {
                    if (file.is_regular_file())
                    {
                        files.push_back(file.path());
                    }
                }
            }

            return BayanSettings{files, std::abs(std::atoi(block_size.c_str()))};

        }
        catch(std::exception& e) {
            std::cerr << "error: " << e.what() << "\n";
            return {};
        }

        catch (...)
        {
            std::cout << "SMTH WENT WRONG" << std::endl;
        }

        return BayanSettings{};

    }
};

std::unique_ptr<ICommandLineParser> CommandLineParserFactory::Create()
{
    return std::make_unique<CommandLineParser>(); 
}

}
