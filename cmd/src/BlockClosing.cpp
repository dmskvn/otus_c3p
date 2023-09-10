#include "BlockClosing.hpp"

namespace cmd
{

std::vector<std::string> BlockClosing::execute(ICommandStorage& strg)
{
    strg.BlockClosing();
    if (!strg.Block())
    {
        return strg.Release();
    }
    else
    {
        return {};
    }  
}

}
