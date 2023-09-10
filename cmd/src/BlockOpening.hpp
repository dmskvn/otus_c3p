#pragma once

#include <cmd/ICommand.hpp>

namespace cmd
{

class BlockOpening : public ICommand
{
public:

    explicit
    BlockOpening()
    {}

    virtual std::vector<std::string> execute(ICommandStorage& strg) override;

};

}
