#pragma once

#include "ICommand.hpp"

#include <memory>
#include <string>

namespace cmd
{
    class ICommandFactory
    {
    public:
        virtual std::unique_ptr <ICommand> Create(std::string cmd) = 0;
        virtual ~ICommandFactory() = default;
    };

std::unique_ptr<ICommandFactory> CreateCommandFactory(std::size_t package_size);
}
