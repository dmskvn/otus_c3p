#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <ip_template/IPTemplate.hpp>

int main() {
    ip_template::print( int8_t{-1} ); // 255
    ip_template::print( int16_t{0} ); // 0.0
    ip_template::print( int32_t{2130706433} ); // 127.0.0.1
    ip_template::print( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    ip_template::print( std::string("Hello World!") ); // Hello, World!
    ip_template::print( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    ip_template::print( std::list<int>{400, 300, 200, 100} ); // 400.300.200.100
    ip_template::print( std::make_tuple<int>(123, 456, 789, 0) ); // 123.456.789.0
}
