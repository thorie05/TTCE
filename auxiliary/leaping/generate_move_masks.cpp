#include "bits/stdc++.h"
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


void printHexLookup(const array<U64, 64>& lookup) {
    /*
    prints the contents of a lookup array in hexadecimal and formats it
    */

    int tabSize = 4;
    int currentLineLength = tabSize;
    cout << "    ";
    for (int i = 0; i < 64; i++) {
        int nextLength = 4;
        if (lookup[i] > 0) {
            nextLength = 4 + log(lookup[i]) / log(16);
        }
        if (currentLineLength + 1 + nextLength > 80) {
            currentLineLength = tabSize;
            cout << endl << "    ";
        }
        if (currentLineLength != tabSize) {
            cout << " ";
            currentLineLength++;
        }
        currentLineLength += nextLength;
        cout << "0x" << hex << lookup[i] << ",";
    }
    cout << endl;
}


int main() {
    array<U64, 64> whitePawnMoveMasks;
    array<U64, 64> whitePawnAttackMasks;
    array<U64, 64> knightMoveMasks;
    array<U64, 64> kingMoveMasks;

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

    for (int sq = 0; sq < 64; sq++) {
        U64 moveMask = 0ULL;
        U64 attackMask = 0ULL;

        int file = sq % 8;
        int rank = sq / 8;

        if (rank + 1 < 8) {
            moveMask |= 1ULL << (sq + 8);

            if (file - 1 >= 0) {
                attackMask |= 1ULL << (sq + 7);
            }
            if (file + 1 < 8) {
                attackMask |= 1ULL << (sq + 9);
            }
        }

        whitePawnMoveMasks[sq] = moveMask;
        whitePawnAttackMasks[sq] = attackMask;
    }

    cout << "white pawn moves:" << endl;
    printHexLookup(whitePawnMoveMasks);

    cout << "white pawn attack:" << endl;
    printHexLookup(whitePawnAttackMasks);

    cout << "knights:" << endl;
    printHexLookup(knightMoveMasks);

    cout << "king:" << endl;
    printHexLookup(kingMoveMasks);

    return 0;
}
