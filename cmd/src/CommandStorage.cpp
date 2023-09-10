#include "CommandStorage.hpp"

namespace cmd
{
    void CommandStorage::Aquire(std::string cmd)
    {
        _strg.push_back(std::move(cmd));
    }

    std::size_t CommandStorage::CmdCount()
    {
        return _strg.size();
    }

    std::vector<std::string> CommandStorage::Release()
    {
        return std::move(_strg);
    }

    void CommandStorage::BlockOpening()
    {
        _braces_ctr++;
    }

    void CommandStorage::BlockClosing()
    {
        _braces_ctr--;
    }

    std::size_t CommandStorage::Block() const
    {
        return _braces_ctr;
    }

    std::unique_ptr<ICommandStorage> CreateStorage()
    {
        return std::make_unique <CommandStorage> ();
    }

}
