#include "CommandFactory.hpp"

#include "Add.hpp"
#include "BlockClosing.hpp"
#include "BlockOpening.hpp"
#include <memory>
#include <string>

#include <iostream>

namespace cmd
{

CommandFactory::CommandFactory(std::size_t package_size)
    :_package_size(package_size)
{}

std::unique_ptr <ICommand> CommandFactory::Create(std::string cmd)
{
    if (cmd == "{")
    {
        return std::make_unique <BlockOpening>();
    }

    if (cmd == "}")
    {
        return std::make_unique <BlockClosing>(_package_size);
    }

    return std::make_unique <Add> ((_package_size), std::move(cmd));
}

std::unique_ptr<ICommandFactory> CreateCommandFactory(std::size_t package_size)
{
    return std::make_unique <CommandFactory> (package_size);
}

}
