#pragma once

#include <ip_filter/IPFilter.hpp>

#include <vector>
#include <set>

namespace ip_filter
{

class IPFilterImpl : public IPFilter
{

    std::vector<IPFilterPredicate> filters;
    std::vector<std::multiset<IP>> filtered;

  public:

    void PushFilter(IPFilterPredicate checker) override;

    void PushIP(IP ip) override;

    std::vector<IP> GetResult() override;

};

}; // namespace ip_filter