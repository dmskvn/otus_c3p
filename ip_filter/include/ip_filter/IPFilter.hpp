#pragma once

#include <string>
#include <functional>
#include <memory>
#include <tuple>

namespace ip_filter
{

using IP = std::tuple <int, int, int, int>;
using IPFilterPredicate =  std::function<bool(const IP&)>;

class IPFilter
{

  public:

    virtual void PushFilter(IPFilterPredicate checker) = 0;

    virtual void PushIP(IP ip) = 0;

    virtual std::vector<IP> GetResult() = 0;

    ~IPFilter() = default;
    
};

struct IPFilterFactory
{
    std::unique_ptr<IPFilter> operator()();
};

}; // namespace version_provider