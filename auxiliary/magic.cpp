#include "bits/stdc++.h"
#include "generate_keys_values.hpp"
#include "generate_magic_numbers.hpp"
#include "construct_lookup_arrays.hpp"
#include "write_magic.hpp"
using namespace std;

typedef unsigned long long U64;


void printBoard(const U64& board) {
    /*
    prints a board given in bitboard representation
    */

    for (int i = 56; i >= 0; i++) {
        if (board & 1ULL << i) {
            cout << 1;
        }
        else {
            cout << 0;
        }
        if ((i + 1) % 8 == 0) {
            i -= 16;
            cout << endl;
        }
    }
    cout << endl;
}


int main() {
    // generate relevant occupancy masks and lookup tables

    array<U64, 64> bishopMasks;
    array<U64, 64> rookMasks;
    array<unordered_map<U64, U64>, 64> bishopLookupTable;
    array<unordered_map<U64, U64>, 64> rookLookupTable;

    getMasksAndLookupTables(bishopMasks, rookMasks, bishopLookupTable,
        rookLookupTable);

    // search for magic numbers

    array<int, 64> bishopShifts;
    array<U64, 64> bishopMagicNumbers;
    array<int, 64> rookShifts;
    array<U64, 64> rookMagicNumbers;

    int numberOfTrys = 10000;

    for (int sq = 0; sq < 64; sq++) {
        cout << sq + 1 << " / 64" << endl;
        // bishops
        pair<U64, U64> bishopMagic = findMagicNumber(numberOfTrys,
            bishopLookupTable[sq]);
        bishopShifts[sq] = bishopMagic.first;
        bishopMagicNumbers[sq] = bishopMagic.second;

        // rooks
        pair<U64, U64> rookMagic = findMagicNumber(numberOfTrys,
            rookLookupTable[sq]);
        rookShifts[sq] = rookMagic.first;
        rookMagicNumbers[sq] = rookMagic.second;
    }

    array<int, 64> bishopLookupIndex;
    array<int, 64> rookLookupIndex;

    vector<U64> bishopLookupArray;
    vector<U64> rookLookupArray;

    constructLookupArrays(bishopLookupTable, rookLookupTable, bishopShifts,
        bishopMagicNumbers, rookShifts, rookMagicNumbers, bishopLookupIndex,
        bishopLookupArray, rookLookupIndex, rookLookupArray);

    cout << "size of bishop lookup array: " << bishopLookupArray.size() << endl;
    cout << "size of rook lookup array: " << rookLookupArray.size() << endl;

    writeMagic("../engine/data/bishop_magic.dat", bishopMagicNumbers,
        bishopShifts, bishopMasks, bishopLookupIndex, bishopLookupArray);
    writeMagic("../engine/data/rook_magic.dat", rookMagicNumbers,
        rookShifts, rookMasks, rookLookupIndex, rookLookupArray);

    return 0;
}