#pragma once

#include <cmd/ICommand.hpp>

namespace cmd
{

class Add : public ICommand
{
    public:

    explicit
    Add(std::size_t limit, std::string cmd)
    :m_limit(limit)
    ,m_cmd(std::move(cmd)) 
    {}

    virtual std::vector<std::string> execute (ICommandStorage& strg) override;

    private:

    const std::size_t m_limit = 0;
    std::string m_cmd{};
};

}
