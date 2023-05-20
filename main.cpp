#include <iostream>
#include <sstream>

#include <ip_filter/IPFilter.hpp>

ip_filter::IP string_to_ip(const std::string& ip)
{
    std::stringstream s(ip);
    int b1, b2, b3, b4;
    char ch; 
    s >> b1
        >> ch >> b2 
        >> ch >> b3
        >> ch >> b4; 
    return {b1,b2,b3,b4};
}

std::string ip_to_string (const ip_filter::IP& ip)
{
    std::stringstream s;
    s << std::get<0>(ip) << "." << std::get<1>(ip) << "." <<  std::get<2>(ip) << "." << std::get<3>(ip);
    return s.str();  
}

int main ()
{
    auto ipFilter = ip_filter::IPFilterFactory{}();
    
    auto accept_all = [](const ip_filter::IP&){return true;};

    auto accept_if_first_byte_is_1 = [](const ip_filter::IP& s){
        return std::get<0>(s) == 1;
    };

    auto accept_if_first_46_and_second_70 = [](const ip_filter::IP& s){
       return (std::get<0>(s) == 46) && (std::get<1>(s) == 70); 
    };

    auto accept_if_any_46 = [](const ip_filter::IP& s){
        return (std::get<0>(s) == 46) || 
        (std::get<1>(s) == 46) || 
        (std::get<2>(s) == 46) || 
        (std::get<3>(s) == 46); 
    };

    ipFilter->PushFilter(std::move(accept_all));
    ipFilter->PushFilter(std::move(accept_if_first_byte_is_1));
    ipFilter->PushFilter(std::move(accept_if_first_46_and_second_70));
    ipFilter->PushFilter(std::move(accept_if_any_46));

    std::string input;
    for (;;)
    {
        std::getline (std::cin, input);
        if (input.empty()) {break;}
        
        auto ip = std::string (input.begin(),
            input.begin() + input.find_first_of("\t"));

        ipFilter->PushIP(string_to_ip(ip));
    }

    auto res = ipFilter->GetResult();
    for (const auto& ip : res)
    {
        std::cout << ip_to_string(ip) << std::endl;
    }

}