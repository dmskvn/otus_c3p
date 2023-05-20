#include "IPFilterImpl.hpp"

#include <iostream>

namespace ip_filter
{

void IPFilterImpl::PushFilter(IPFilterPredicate filter)
{
    filters.push_back(std::move(filter));
}

void IPFilterImpl::PushIP(IP ip)
{
    if (filtered.empty())
    {
        for (std::size_t i = 0; i < filters.size(); ++i)
        {
            filtered.emplace_back();
        }
    }

    for (std::size_t i = 0; i < filters.size(); ++i)
    {
        if (filters[i](ip))
        {
            filtered[i].insert(ip);
        }
    }
}

std::vector<IP> IPFilterImpl::GetResult()
{
    std::vector<IP> res;

    for (const auto& ips : filtered)
    {
        for (auto it = ips.rbegin(); it != ips.rend(); it++)
        {
            // std::cout << "Get from strg " << std::get<0>(*it)
            // << "." << std::get<1>(*it) << "." << std::get<2>(*it)
            // << "." << std::get<3>(*it) << std::endl;
            res.push_back(*it);
        }
    }

    return res;
}

std::unique_ptr<IPFilter> IPFilterFactory::operator()()
{
    return std::make_unique<IPFilterImpl>();
}

} // namespace ip_processor