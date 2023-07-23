#include "BlockOpening.hpp"

namespace cmd
{

std::vector<std::string> BlockOpening::execute(ICommandStorage& strg)
{
    strg.BlockOpening();
    return strg.Release();
}

}