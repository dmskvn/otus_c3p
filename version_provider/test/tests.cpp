#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <version_provider/VersionProvider.hpp>

TEST(TestVersionProvider, MoreThanZero)
{
    const auto versionProvider = version_provider::VersionProviderFactory{}();
    EXPECT_GT(versionProvider->GetVersion(), 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}