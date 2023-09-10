#pragma once

#include <string>
#include <vector>
#include <memory>

namespace cmd
{

class ICommandStorage
{
    public:

    virtual void Aquire(std::string cmd) = 0;
    virtual std::size_t CmdCount() = 0;
    virtual std::vector<std::string> Release() = 0;
    virtual void BlockOpening() = 0;
    virtual void BlockClosing() = 0;
    virtual std::size_t Block() const = 0;

    virtual ~ICommandStorage() = default;
};

std::unique_ptr<ICommandStorage> CreateStorage();

}
