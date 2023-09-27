#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <chrono>

#include <cmd/ICommandStorage.hpp>
#include <cmd/ICommandFactory.hpp>


int main(int argc, char *argv[]) {

    if (argc != 2)
    {
        std::logic_error ("Only one parameter expected");
    }

    std::size_t pkg_size = std::atoi(argv[1]);

    auto factory = cmd::CreateCommandFactory(pkg_size);
    auto strg = cmd::CreateStorage();
    auto line = std::string{};
    auto fout = std::fstream{};
    bool should_init_fout = true;

    while (std::getline(std::cin, line))
    {
        auto cmd = factory->Create(line);
        auto pkg = cmd->execute(*strg);

        if (should_init_fout)
        {
            const auto clock = std::chrono::system_clock::now();
            const auto time = std::chrono::duration_cast<std::chrono::seconds>(
                   clock.time_since_epoch()).count();

            fout.open("bulk"+std::to_string(time)+"log", std::fstream::out);
        }

        if (!pkg.empty())
        {
            std::cout << "bulk:";
            fout << "bulk:";

            for (const auto& cmnd : pkg)
            {
                std::cout << cmnd << " ";
                fout << cmnd << " ";
            }
            std::cout << "\n";
            fout << "\n";
        }
    }

    std::cout << std::endl;
    fout.flush();
    fout.close();

}
