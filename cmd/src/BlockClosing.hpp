#pragma once

#include <cmd/ICommand.hpp>

namespace cmd
{

class BlockClosing : public ICommand
{
public:

    explicit
    BlockClosing(std::size_t limit)
    :m_limit(limit)
    {}

    virtual std::vector<std::string> execute (ICommandStorage& strg) override;

    private:

    const std::size_t m_limit = 0;
};

}
