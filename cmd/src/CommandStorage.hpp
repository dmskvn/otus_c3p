#pragma once 

#include <cmd/ICommandStorage.hpp>

#include <vector>
#include <string>

namespace cmd
{

class CommandStorage : public ICommandStorage
{

public:

    virtual void Aquire(std::string cmd) override;
    virtual std::size_t CmdCount() override;
    virtual std::vector<std::string> Release() override;
    virtual void BlockOpening() override;
    virtual void BlockClosing() override;
    virtual bool InBlock() const override;

    private:

    std::vector<std::string> _strg{};
    std::size_t _braces_ctr = 0;

};

}