#pragma once

#include <vector>
#include <string>
#include <memory>

namespace byn
{

class IFilesProcessor
{

public:

    virtual std::vector<std::vector<std::string>> process (std::vector<std::string> files, std::size_t gap) = 0;
    ~IFilesProcessor () = default;
};

struct FilesProcessorFactory
{
    static std::unique_ptr <IFilesProcessor> Create();
};

} // namespace byn
