#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;


void constructLookupArrays(
    const array<unordered_map<U64, U64>, 64>& bishopLookupTable,
    const array<unordered_map<U64, U64>, 64>& rookLookupTable,
    const array<int, 64>& bishopShifts,
    const array<U64, 64>& bishopMagicNumbers, const array<int, 64>& rookShifts,
    const array<U64, 64>& rookMagicNumbers, array<int, 64>& bishopLookupIndex,
    vector<U64>& bishopLookupArray, array<int, 64>& rookLookupIndex,
    vector<U64>& rookLookupArray) {
    /*
    constructs the lookup arrays and index arrays for bishops and rooks using
    the given magic numbers and lookup tables
    */

    int bishopCurrentIndex = 0;
    int rookCurrentIndex = 0;

    for (int sq = 0; sq < 64; sq++) {
        // bishops

        bishopLookupIndex[sq] = bishopCurrentIndex;
        // construct lookup array for current square
        vector<U64> bishopLookupSquare(1 << (64 - bishopShifts[sq]));
        for (auto& it: bishopLookupTable[sq]) {
            U64 oldKey = it.first;
            U64 newKey = (oldKey * bishopMagicNumbers[sq]) >> bishopShifts[sq];
            bishopLookupSquare[newKey] = it.second;
        }
        // remove unnecessary trailing zeros
        while (bishopLookupSquare.back() == 0) {
            bishopLookupSquare.pop_back();
        }
        // add to lookup array for all squares
        for (int i = 0; i < bishopLookupSquare.size(); i++) {
            bishopLookupArray.push_back(bishopLookupSquare[i]);
        }
        bishopCurrentIndex += bishopLookupSquare.size();

        // rooks

        rookLookupIndex[sq] = rookCurrentIndex;
        // construct lookup array for current square
        vector<U64> rookLookupSquare(1 << (64 - rookShifts[sq]));
        for (auto& it: rookLookupTable[sq]) {
            U64 oldKey = it.first;
            U64 newKey = (oldKey * rookMagicNumbers[sq]) >> rookShifts[sq];
            rookLookupSquare[newKey] = it.second;
        }
        // remove unused trailing indices
        while (rookLookupSquare.back() == 0) {
            rookLookupSquare.pop_back();
        }
        // add to lookup array
        for (int i = 0; i < rookLookupSquare.size(); i++) {
            rookLookupArray.push_back(rookLookupSquare[i]);
        }
        rookCurrentIndex += rookLookupSquare.size();
    }
}
