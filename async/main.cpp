#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>
#include "include/async/async.h"


int main(int argc, char *argv[]) {

    if (argc != 2)
    {
        throw std::logic_error ("Only one parameter expected");
    }

    std::size_t pkg_size = std::atoi(argv[1]);

    auto line = std::string{};
    auto fout = std::fstream{};
    bool should_init_fout = true;

    int f1 = async::connect(pkg_size);
    int f2 = async::connect(pkg_size);

    while (std::getline(std::cin, line))
    {
        async::receive(f1, line.c_str(), line.size());
        async::receive(f2, line.c_str(), line.size());
    }

    async::disconnect(f1);
    async::disconnect(f2);
}
