#include "bits/stdc++.h"
#include "../helper_functions.hpp"
using namespace std;

typedef unsigned long long U64;


int main() {
    vector<U64> knightMoveMasks(64);
    vector<U64> kingMoveMasks(64);

    // knights
    for (int sq = 0; sq < 64; sq++) {
        U64 mask = 0ULL;

        int file = sq % 8;
        int rank = sq / 8;

        // left
        if (file - 2 >= 0 && rank - 1 >= 0) {
            mask |= 1ULL << (sq - 10);
        }
        if (file - 2 >= 0 && rank + 1 < 8) {
            mask |= 1ULL << (sq + 6);
        }
        // upper
        if (file - 1 >= 0 && rank + 2 < 8) {
            mask |= 1ULL << (sq + 15);
        }
        if (file + 1 < 8 && rank + 2 < 8) {
            mask |= 1ULL << (sq + 17);
        }
        // right
        if (file + 2 < 8 && rank - 1 >= 0) {
            mask |= 1ULL << (sq - 6);
        }
        if (file + 2 < 8 && rank + 1 < 8) {
            mask |= 1ULL << (sq + 10);
        }
        // lower
        if (file - 1 >= 0 && rank - 2 >= 0) {
            mask |= 1ULL << (sq - 17);
        }
        if (file + 1 < 8 && rank - 2 >= 0) {
            mask |= 1ULL << (sq - 15);
        }

        knightMoveMasks[sq] = mask;
    }

    for (int sq = 0; sq < 64; sq++) {
        U64 mask = 0ULL;

        int file = sq % 8;
        int rank = sq / 8;

        // left
        if (file - 1 >= 0) {
            mask |= 1ULL << (sq - 1);
        }
        // upper left
        if (file - 1 >= 0 && rank + 1 < 8) {
            mask |= 1ULL << (sq + 7);
        }
        // upper
        if (rank + 1 < 8) {
            mask |= 1ULL << (sq + 8);
        }
        // upper right
        if (file + 1 < 8 && rank + 1 < 8) {
            mask |= 1ULL << (sq + 9);
        }
        // right
        if (file + 1 < 8) {
            mask |= 1ULL << (sq + 1);
        }
        // lower right
        if (file + 1 < 8 && rank - 1 >= 0) {
            mask |= 1ULL << (sq - 7);
        }
        // lower
        if (rank - 1 >= 0) {
            mask |= 1ULL << (sq - 8);
        }
        // lower left
        if (file - 1 >= 0 && rank - 1 >= 0) {
            mask |= 1ULL << (sq - 9);
        }

        kingMoveMasks[sq] = mask;
    }

    cout << "knights:" << endl;
    printHexLookup(knightMoveMasks);

    cout << "king:" << endl;
    printHexLookup(kingMoveMasks);

    return 0;
}
