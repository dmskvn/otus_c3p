#include "BlockClosing.hpp"

namespace cmd
{

std::vector<std::string> BlockClosing::execute(ICommandStorage& strg)
{
    strg.BlockClosing();
    if (!strg.InBlock() && strg.CmdCount() >= m_limit)
    {
        return strg.Release();
    }
    else
    {
        return {};
    }  
}

}