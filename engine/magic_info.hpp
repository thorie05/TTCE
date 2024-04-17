#ifndef MAGIC_INFO_HPP
#define MAGIC_INFO_HPP

#include <array>
#include <iostream>

typedef unsigned long long U64;

struct MagicInfo {
    std::array<U64, 100> lookupRooks;

    MagicInfo() {
        std::cout << "init magic info" << std::endl;
    }
};

#endif
