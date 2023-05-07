#pragma once 

#include <memory>
#include <string>

namespace version_provider
{

class IVersionProvider
{

  public:

    virtual int GetVersion() const = 0;

    ~IVersionProvider() = default;
};

struct VersionProviderFactory
{
    std::unique_ptr<IVersionProvider> operator()();
};

} // namespace version_provider