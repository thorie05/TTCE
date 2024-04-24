#ifndef MAGIC_INFO_HPP
#define MAGIC_INFO_HPP

#include "constants.hpp"
#include <array>
#include <vector>
#include <iostream>
#include <fstream>

typedef unsigned long long U64;


struct MagicInfo {
    // bishops
    std::array<U64, 64> bishopMagicNumbers;
    std::array<int, 64> bishopShifts;
    std::array<U64, 64> bishopMasks;
    std::array<int, 64> bishopLookupIndex;
    std::vector<U64> bishopLookup;

    // rooks
    std::array<U64, 64> rookMagicNumbers;
    std::array<int, 64> rookShifts;
    std::array<U64, 64> rookMasks;
    std::array<int, 64> rookLookupIndex;
    std::vector<U64> rookLookup;

    MagicInfo() {
        // read bishops

        std::ifstream bishopFile("engine/data/bishop_magic.dat", 
            std::ios::binary);
        if (!bishopFile.is_open()) {
            std::cerr << "Error opening bishop_magic.dat for reading.\n";
        }

        // magic numbers
        bishopFile.read(reinterpret_cast<char*>(bishopMagicNumbers.data()), 
            64 * sizeof(U64));
        // shifts
        bishopFile.read(reinterpret_cast<char*>(bishopShifts.data()), 
            64 * sizeof(int));
        // masks
        bishopFile.read(reinterpret_cast<char*>(bishopMasks.data()), 
            64 * sizeof(U64));
        // lookup index
        bishopFile.read(reinterpret_cast<char*>(bishopLookupIndex.data()), 
            64 * sizeof(int));

        // read lookup size
        size_t bishopLookupSize;
        bishopFile.read(reinterpret_cast<char*>(&bishopLookupSize),
            sizeof(size_t));
        bishopLookup.resize(bishopLookupSize);

        // read lookup vector
        bishopFile.read(reinterpret_cast<char*>(bishopLookup.data()), 
            bishopLookupSize * sizeof(U64));

        bishopFile.close();

        // read rooks

        std::ifstream rookFile("engine/data/rook_magic.dat", std::ios::binary);
        if (!rookFile.is_open()) {
            std::cerr << "Error opening rook_magic.dat for reading.\n";
        }

        // magic numbers
        rookFile.read(reinterpret_cast<char*>(rookMagicNumbers.data()), 
            64 * sizeof(U64));
        // shifts
        rookFile.read(reinterpret_cast<char*>(rookShifts.data()), 
            64 * sizeof(int));
        // masks
        rookFile.read(reinterpret_cast<char*>(rookMasks.data()), 
            64 * sizeof(U64));
        // lookup index
        rookFile.read(reinterpret_cast<char*>(rookLookupIndex.data()), 
            64 * sizeof(int));

        // read lookup size
        size_t rookLookupSize;
        rookFile.read(reinterpret_cast<char*>(&rookLookupSize), sizeof(size_t));
        rookLookup.resize(rookLookupSize);

        // read lookup vector
        rookFile.read(reinterpret_cast<char*>(rookLookup.data()), 
            rookLookupSize * sizeof(U64));

        rookFile.close();
    }
};

#endif
