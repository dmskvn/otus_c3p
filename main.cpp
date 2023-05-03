#include <iostream>

#include <version_provider/VersionProvider.hpp>

int main ()
{
    auto versionProviderFactory = version_provider::VersionProviderFactory{}();
    std::cout << versionProviderFactory->GetVersion() << std::endl;
}