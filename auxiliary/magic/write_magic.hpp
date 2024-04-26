#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;


void writeMagic(std::string filename, std::array<U64, 64> magicNumbers,
    std::array<int, 64> shifts, std::array<U64, 64> masks,
    std::array<int, 64> lookupIndex, std::vector<U64> lookup) {
    /*
    writes the magic info into a binary in the following format:
    - magic numbers (U64)
    - shifts (int)
    - relevant occupancy masks (U64)
    - lookup index array (int)
    - lookup array size (size_t)
    - lookup array (U64)
    */

    std::ofstream file(filename, std::ios::binary);

    // write shifts
    for (const auto& value : shifts) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }

    // write magic numbers
    for (const auto& value : magicNumbers) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(U64));
    }

    // write masks
    for (const auto& value : masks) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(U64));
    }

    // write lookup index array
    for (const auto& value : lookupIndex) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }

    // write lookup size
    size_t lookupSize = lookup.size();
    file.write(reinterpret_cast<const char*>(&lookupSize), sizeof(size_t));

    // write lookup array
    for (const auto& value : lookup) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(U64));
    }

    file.close();
}
