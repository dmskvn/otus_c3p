#include "Add.hpp"

#include <iostream>

namespace cmd
{

std::vector<std::string> Add::execute(ICommandStorage& strg)
{
    strg.Aquire(std::move(m_cmd));
    if (!strg.InBlock() && strg.CmdCount() == m_limit)
    {
        return strg.Release();
    }
    else
    {
        return {};
    }
    
}

}
