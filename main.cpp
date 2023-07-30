#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <string>
//#include <cmd/ICommandStorage.hpp>
//#include <cmd/ICommandFactory.hpp>
#include <matrix/Matrix.hpp>
#include <cassert>

int main(/*int argc, char *argv[]*/) {

//    if (argc != 2)
//    {
//        std::logic_error ("Only one parameter expected");
//    }

//    std::size_t pkg_size = std::atoi(argv[1]);

//    auto factory = cmd::CreateCommandFactory(pkg_size);
//    auto strg = cmd::CreateStorage();
//    auto line = std::string{};

//    while (std::getline(std::cin, line))
//    {
//        auto cmd = factory->Create(line);
//        auto pkg = cmd->execute(*strg);

//        for (const auto cmnd : pkg)
//        {
//            std::cout << cmnd << " ";
//        }
//        std::cout << std::endl;
//    }

     matrix::Matrix<int, -1> matrix;
     assert(matrix.size() == 0);
     auto a = matrix[0][0];
     assert(a == -1);
     assert(matrix.size() == 0);
     matrix[100][100] = 314;
     assert(matrix[100][100] == 314);
     assert(matrix.size() == 1);

     for (const auto e : matrix)
     {
        std::cout << e << std::endl;
     }
   
}
