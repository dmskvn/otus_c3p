#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <regex>
#include <ip_filter/IPFilter.hpp>

using namespace std::string_literals;

TEST(TestIpFilter, CorrectFilter_1_2_3_4)
{
    const auto ipprc = ip_filter::IPFilterFactory{}();
    auto accept_1_2_3_4 = [](const ip_filter::IP& s){
        return std::get<0>(s) == 1 && std::get<1>(s) == 2 &&
        std::get<2>(s) == 3 && std::get<3>(s) == 4; 
    };

    ipprc->PushFilter(std::move(accept_1_2_3_4));

    ipprc->PushIP(std::make_tuple(0,0,0,0));
    ipprc->PushIP(std::make_tuple(1,2,3,4));
    ipprc->PushIP(std::make_tuple(4,3,2,1));
    
    auto res = ipprc->GetResult();

    EXPECT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], std::make_tuple(1,2,3,4));  
}

TEST(TestIpFilter, CheckOrder)
{
    const auto ipprc = ip_filter::IPFilterFactory{}();
    auto accept_all = [](const ip_filter::IP& s){
        return true; 
    };

    ipprc->PushFilter(std::move(accept_all));

    ipprc->PushIP(std::make_tuple(0,0,0,0));
    ipprc->PushIP(std::make_tuple(1,2,3,4));
    ipprc->PushIP(std::make_tuple(4,3,2,1));
    
    auto res = ipprc->GetResult();

    EXPECT_EQ(res.size(), 3);
    EXPECT_EQ(res[0], std::make_tuple(4,3,2,1));
    EXPECT_EQ(res[1], std::make_tuple(1,2,3,4));
    EXPECT_EQ(res[2], std::make_tuple(0,0,0,0));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}