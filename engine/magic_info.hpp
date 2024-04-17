#ifndef MAGIC_INFO_HPP
#define MAGIC_INFO_HPP

#include "constants.hpp"
#include <array>
#include <iostream>
#include <fstream>

typedef unsigned long long U64;

struct MagicInfo {
    // bishops
    std::array<U64, 64> bishopMagicNumbers;
    std::array<int, 64> bishopShifts;
    std::array<U64, 64> bishopMasks;
    std::array<int, 64> bishopLookupIndex;
    std::array<U64, MAGIC_BISHOP_LOOKUP_SIZE> bishopLookup;

    // rooks
    std::array<U64, 64> rookMagicNumbers;
    std::array<int, 64> rookShifts;
    std::array<U64, 64> rookMasks;
    std::array<int, 64> rookLookupIndex;
    std::array<U64, MAGIC_ROOK_LOOKUP_SIZE> rookLookup;

    MagicInfo() {
        // read bishop info
        std::ifstream bishopFile("engine/magic/bishop_magic.dat", 
            std::ios::binary);
        if (!bishopFile.is_open()) {
            std::cerr << "Error opening bishop_magic.dat for reading\n";
        }

        // magic numbers
        bishopFile.read(reinterpret_cast<char*>(bishopMagicNumbers.data()), 
            64 *sizeof(U64));
        // shifts
        bishopFile.read(reinterpret_cast<char*>(bishopShifts.data()), 
            64 * sizeof(int));
        // masks
        bishopFile.read(reinterpret_cast<char*>(bishopMasks.data()), 
            64 * sizeof(U64));
        // lookup index
        bishopFile.read(reinterpret_cast<char*>(bishopLookupIndex.data()), 
            64 * sizeof(int));
        // lookup
        bishopFile.read(reinterpret_cast<char*>(bishopLookup.data()), 
            MAGIC_BISHOP_LOOKUP_SIZE * sizeof(U64));

        bishopFile.close();

        // read rook info
        std::ifstream rookFile("engine/magic/rook_magic.dat", std::ios::binary);
        if (!rookFile.is_open()) {
            std::cerr << "Error opening rook_magic.dat for reading\n";
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
        // lookup
        rookFile.read(reinterpret_cast<char*>(rookLookup.data()), 
            MAGIC_BISHOP_LOOKUP_SIZE * sizeof(U64));

        rookFile.close();
    }
};

#endif
