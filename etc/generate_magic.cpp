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

    vector<U64> rookMaskWithoutBorder(64);

    for (int i = 0; i < 64; i++) {
        U64 mask = 0;

        int j = i + 8;
        while (j < 56) {
            mask |= 1ULL << j;
            j += 8;
        }
        j = i - 8;
        while (j >= 8) {
            mask |= 1ULL << j;
            j -= 8;
        }
        j = i - 1;
        while (j > i - i % 8) {
            mask |= 1ULL << j;
            j--;
        }
        j = i + 1;
        while (j < i - i % 8 + 7) {
            mask |= 1ULL << j;
            j++;
        }

        rookMaskWithoutBorder[i] = mask;
    }

    vector<vector<U64>> keys(64);

    for (int s = 0; s < 64; s++) {
        U64 board = rookMaskWithoutBorder[s];

        vector<int> enemyPieces;
        for (int i = 0; i < 64; i++) {
            if (board & 1ULL << i) {
                enemyPieces.push_back(i);
            }
        }

        for (int i = 0; i < 1 << enemyPieces.size(); i++) {
            U64 blockers = 0;
            for (int j = 0; j < enemyPieces.size(); j++) {
                if (i & 1 << j) {
                    blockers |= 1ULL << enemyPieces[j];
                }
            }
            keys[s].push_back(blockers);
        }
    }

    vector<vector<U64>> values(64);

    for (int i = 0; i < 64; i++) {
        for(int j = 0; j < keys[i].size(); j++) {
            U64 blockers = keys[i][j];
            U64 moves = 0;

            int k = i + 8;
            while (k < 64) {
                moves |= 1ULL << k;
                if (blockers & 1ULL << k) break;
                k += 8;
            }
            k = i - 8;
            while (k >= 0) {
                moves |= 1ULL << k;
                if (blockers & 1ULL << k) break;
                k -= 8;
            }
            k = i - 1;
            while (k >= i - i % 8) {
                moves |= 1ULL << k;
                if (blockers & 1ULL << k) break;
                k--;
            }
            k = i + 1;
            while (k <= i - i % 8 + 8) {
                moves |= 1ULL << k;
                if (blockers & 1ULL << k) break;
                k++;
            }
            values[i].push_back(moves);
        }
    }

    ofstream RookKeys("rook_keys");
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < keys[i].size(); j++) {
            RookKeys << keys[i][j] << " ";
        }
        RookKeys << endl;
    }
    RookKeys.close();

    ofstream RookValues("rook_values");
    for (int i = 0; i < 64; i++) {
        RookValues << i << endl;
        for (int j = 0; j < values[i].size(); j++) {
            RookValues << values[i][j] << " ";
        }
        RookValues << endl;
    }
    RookValues.close();

    return 0;
}