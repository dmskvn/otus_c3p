#include "FilesProcessor.hpp"

#include <string>
#include <algorithm>
#include <memory>
#include <future>

#include <iostream>

namespace byn
{

    std::vector<std::vector<std::string>> FilesProcessor::process (std::vector<std::string> files, std::size_t gapSize)
    {
        std::vector <FilesProcessor::FileContext> filesCntx;

        for (const auto& file : files)
        {
            auto strm = std::fstream{};
            strm.open(file, std::ios_base::in);
            filesCntx.push_back({file, std::move(strm), ""});
        }


        ProcessFilesGroup(filesCntx.begin(), filesCntx.end(), gapSize);

        std::vector<std::vector<std::string>> res;
        res.push_back({});
        res.back().push_back(filesCntx.begin()->_path);

        for (auto it = filesCntx.begin() + 1; it != filesCntx.end(); ++it)
        {
            if (it != filesCntx.begin())
            {
                if ((it-1)->_hash != it->_hash)
                {
                    res.push_back({});
                }
            }

            res.back().push_back(it->_path);
        }
        return res;
    }

    
    void FilesProcessor::ProcessFilesGroup(std::vector <FilesProcessor::FileContext>::iterator begin,
        std::vector<FilesProcessor::FileContext>::iterator end, std::size_t gapSize)
    {

        if (begin + 1 == end) return;

        for (auto it = begin; it != end; it++)
        {
            ReadChunkAndClcHash(*it, gapSize);
        }

        std::sort(begin, end, [](FileContext& a, FileContext& b){
            if (!a._strm.is_open())
            {
                return true;
            }
            return a._hash < b._hash;
        });

        auto firstOpened = std::find_if(begin, end, [](const FileContext& a){
            return a._strm.is_open();
        });

        if (firstOpened == end) return;

        auto groupBegin = firstOpened;

        std::vector <std::future<void>> threads;
        for (auto it = begin + 1; it != end; ++it)
        {
            if ((it - 1)->_hash != (it)->_hash)
            {
                auto thread = std::async(std::launch::async,
                    [&]{
                    ProcessFilesGroup(groupBegin, it, gapSize);
                });
                threads.push_back(std::move(thread));
                groupBegin = it;
            }
        }

        for (const auto& thread : threads)
        {
            thread.wait();
        }

        ProcessFilesGroup(groupBegin, end, gapSize);
    }

    void FilesProcessor::ReadChunkAndClcHash(FilesProcessor::FileContext& ctx, std::size_t gapSize)
    {
        if (ctx._strm)
        {
            auto buffer = std::string(gapSize, '0');
            buffer.reserve(gapSize);
            ctx._strm.read(&buffer[0], buffer.size());
            const auto curHash = std::hash<std::string>{}(buffer.c_str());
            ctx._hash += std::to_string(curHash);
            if (ctx._strm.eof()) ctx._strm.close();
        }
    }

    std::unique_ptr <IFilesProcessor> FilesProcessorFactory::Create()
    {
        return std::make_unique<FilesProcessor> ();
    }

};
