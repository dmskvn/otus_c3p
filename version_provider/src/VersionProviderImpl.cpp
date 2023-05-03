#include "VersionProviderImpl.hpp"

#include "version.hpp"

namespace version_provider
{

int VersionProviderImpl::GetVersion() const noexcept
{
    return PROJECT_VERSION_PATCH;
}

std::unique_ptr<IVersionProvider> VersionProviderFactory::operator()()
{
    return std::make_unique<VersionProviderImpl>();
}

} // namespace version_provider