#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <matrix/Matrix.hpp>

int main() {
    
    matrix::Matrix<int, 1> m;

    // ----------

    m[0][0] = 0;
    m[1][1] = 1;
    m[2][2] = 2;
    m[3][3] = 3;
    m[4][4] = 4;
    m[5][5] = 5;
    m[6][6] = 6;
    m[7][7] = 7;
    m[8][8] = 8;
    m[9][9] = 9;

    // ----------
    
    m[0][9] = 0;
    m[1][8] = 1;
    m[2][7] = 2;
    m[3][6] = 3;
    m[4][5] = 4;
    m[5][4] = 5;
    m[6][3] = 6;
    m[7][2] = 7;
    m[8][1] = 8;
    m[9][0] = 9;

    // ----------

    for (std::size_t x = 1; x < 9; ++x)
    {
        for (std::size_t y = 1; y < 9; ++y)
        {
            std::cout << m[x][y] << " ";
        }
        std::cout << '\n';
    }

    for(auto c : m)
    {
        std::size_t x;
        std::size_t y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

}
