#pragma once

#include <cmd/ICommandFactory.hpp>

#include <memory>
#include <string>

namespace cmd
{
class CommandFactory : public ICommandFactory
{
public:

    explicit
    CommandFactory(std::size_t package_size);

    virtual std::unique_ptr <ICommand> Create(std::string cmd) override;

private:

    const std::size_t _package_size = 0;
};

}
