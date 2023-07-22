#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <matrix/Matrix.hpp>

int main() {
    
    matrix::Matrix<int, 1> m;
    m[0][1] = 5;
    m[3][6] = 66;


    for (const auto e : m)
    {
        std::cout << e << std::endl;
    }

}
