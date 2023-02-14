#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <sstream>
#include <vector>

class Util {
public:
    static std::vector<std::string> split_string(std::string line, char delim);
};

#endif