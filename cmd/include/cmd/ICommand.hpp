#pragma once

#include <string>
#include <vector>
#include "ICommandStorage.hpp"

namespace cmd
{

class ICommand
{
public:
    virtual std::vector<std::string> execute(ICommandStorage& strg) = 0;
    virtual ~ICommand() = default;
};

}