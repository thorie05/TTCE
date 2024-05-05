#include "bits/stdc++.h"
#include "../helper_functions.hpp"
using namespace std;

typedef unsigned long long U64;


int main() {
    vector<U64> whitePawnMasks(64);
    vector<U64> whitePawnLookup(1024);
    vector<U64> blackPawnMasks(64);
    vector<U64> blackPawnLookup(1024);

    // white pawn masks
    for (int sq = 0; sq < 64; sq++) {
        U64 mask = 0ULL;

        int file = sq % 8;
        int rank = sq / 8;

        if (rank == 1) {
            mask |= 1ULL << (sq + 16);
        }
        if (rank + 1 < 8) {
            mask |= 1ULL << (sq + 8);
            if (file - 1 >= 0) {
                mask |= 1ULL << (sq + 7);
            }
            if (file + 1 < 8) {
                mask |= 1ULL << (sq + 9);
            }
        }

        whitePawnMasks[sq] = mask;
    }

    // mask for white:
    // first bit: left capture square
    // second bit: push square
    // third bit: right capture square
    // fourth bit: double push square

    // white pawn lookup array
    for (int sq = 0; sq < 56; sq ++) {
        for (int i = 0; i < 16; i++) {
            U64 mask = 0ULL;

            if (!(i & 2)) {
                mask |= 1ULL << (sq + 8);
                if (sq / 8 == 1 && !(i & 8)) {
                    mask |= 1ULL << (sq + 16);
                }
            }
            if (i & 1) {
                mask |= 1ULL << (sq + 7);
            }
            if (i & 4) {
                mask |= 1ULL << (sq + 9);
            }

            whitePawnLookup[sq * 16 + i] = mask;
        }
    }

    // black pawn masks
    for (int sq = 0; sq < 64; sq++) {
        U64 mask = 0ULL;

        int file = sq % 8;
        int rank = sq / 8;

        if (rank == 6) {
            mask |= 1ULL << (sq - 16);
        }
        if (rank - 1 >= 0) {
            mask |= 1ULL << (sq - 8);
            if (file - 1 >= 0) {
                mask |= 1ULL << (sq - 9);
            }
            if (file + 1 < 8) {
                mask |= 1ULL << (sq - 7);
            }
        }

        blackPawnMasks[sq] = mask;
    }

    // mask for black:
    // first bit: double push square
    // second bit: right capture square
    // third bit: push square
    // fourth bit: left capture square

    // black pawn lookup array
    for (int sq = 8; sq < 64; sq ++) {
        for (int i = 0; i < 16; i++) {
            U64 mask = 0ULL;

            if (!(i & 4)) {
                mask |= 1ULL << (sq - 8);
                if (sq / 8 == 6 && !(i & 1)) {
                    mask |= 1ULL << (sq - 16);
                }
            }
            if (i & 2) {
                mask |= 1ULL << (sq - 9);
            }
            if (i & 8) {
                mask |= 1ULL << (sq - 7);
            }

            blackPawnLookup[sq * 16 + i] = mask;
        }
    }

    cout << "white pawn masks:" << endl;
    printHexLookup(whitePawnMasks);

    cout << "white pawn lookup:" << endl;
    printHexLookup(whitePawnLookup);

    cout << "black pawn masks:" << endl;
    printHexLookup(blackPawnMasks);

    cout << "black pawn lookup:" << endl;
    printHexLookup(blackPawnLookup);

    return 0;
}