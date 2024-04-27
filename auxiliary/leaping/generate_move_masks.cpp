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
        int nextLength = 4 + log(lookup[i]) / log(16);
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
    array<U64, 64> knightMoveMasks;

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

    cout << "knights:" << endl;
    printHexLookup(knightMoveMasks);

    return 0;
}
