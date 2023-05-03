#pragma once

#include <version_provider/VersionProvider.hpp>

namespace version_provider
{

class VersionProviderImpl : public IVersionProvider
{
  public:

    int GetVersion() const noexcept override;
};

} // namespace version_provider