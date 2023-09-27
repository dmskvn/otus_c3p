#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <cmd/ICommandStorage.hpp>
#include <cmd/ICommandFactory.hpp>
#include <bayan/ICommandLineParser.hpp>
#include <bayan/IFilesProcessor.hpp>
#include <cassert>

int main(int argc, const char *argv[]) {

   auto parser = byn::CommandLineParserFactory::Create();
   auto parsed = parser->Parse(argv, argc);

   auto fp =  byn::FilesProcessorFactory::Create();

   auto groups = fp->process(parsed.m_files, parsed.block_size);

   for (const auto& group : groups)
   {
       for (const auto& file : group)
       {
           std::cout << file << " " << std::endl;
       }
       std::cout << '\n';
   }

   //std::cout << std::endl;

}

