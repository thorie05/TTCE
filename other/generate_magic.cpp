#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;


void printBoard(U64 board) {
    cout << board << endl;
    for (int i = 0; i < 64; i++) {
        if (board & 1ULL << i) {
            cout << 1;
        }
        else {
            cout << 0;
        }
    }
    cout << endl;
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
    vector<U64> rookMaskSquares(64);

    for (int i = 0; i < 64; i++) {
        U64 rookMask = 0;

        int j = i;
        while (j < 64) {
            rookMask |= 1ULL << j;
            j += 8;
        }
        j = i;
        while (j >= 0) {
            rookMask |= 1ULL << j;
            j -= 8;
        }
        j = i;
        while (j >= i - i % 8) {
            rookMask |= 1ULL << j;
            j--;
        }
        j = i;
        while (j < i - i % 8 + 8) {
            rookMask |= 1ULL << j;
            j++;
        }

        rookMaskSquares[i] = rookMask;
    }

    vector<U64> rookMaskSquaresWithoutBorder(64);

    for (int i = 0; i < 64; i++) {
        U64 rookMask = 0;

        int j = i;
        while (j < 56) {
            rookMask |= 1ULL << j;
            j += 8;
        }
        j = i;
        while (j >= 8) {
            rookMask |= 1ULL << j;
            j -= 8;
        }
        j = i;
        while (j > i - i % 8) {
            rookMask |= 1ULL << j;
            j--;
        }
        j = i;
        while (j < i - i % 8 + 7) {
            rookMask |= 1ULL << j;
            j++;
        }

        rookMaskSquaresWithoutBorder[i] = rookMask;
    }

    U64 board = rookMaskSquaresWithoutBorder[19];
    printBoard(board);

    int enemyPieces = __builtin_popcountll(board) - 1;
    for (int i = 0; i < 1 << enemyPieces; i++) {
        cout << i << endl;
    }

    return 0;
}