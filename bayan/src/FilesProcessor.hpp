#pragma once

#include <bayan/IFilesProcessor.hpp>

#include <fstream> 
#include <vector>

namespace byn
{

class FilesProcessor : public IFilesProcessor
{

public:

    virtual std::vector<std::vector<std::string>> process(std::vector<std::string> directories, std::size_t gapSize) override;

private:

    struct FileContext
    {
        std::string _path;
        std::fstream _strm;
        std::string _hash;
    };

    std::size_t _gapSize = 0;
    
    void ReadChunkAndClcHash(FileContext& ctx, std::size_t gapSize);

    void ProcessFilesGroup (std::vector <FileContext>::iterator begin,
        std::vector<FileContext>::iterator end, std::size_t gapSize);
    
};

} // namespace byn
