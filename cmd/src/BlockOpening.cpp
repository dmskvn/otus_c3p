#include "BlockOpening.hpp"

namespace cmd
{

std::vector<std::string> BlockOpening::execute(ICommandStorage& strg)
{
    strg.BlockOpening();
    if (strg.Block() == 1)
    {
        return strg.Release();
    }
    return {};
}

}
