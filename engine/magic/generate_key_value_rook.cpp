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
    std::ofstream fout("../engine/magics_rook.txt");

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

    cout << "{";
    for (int i = 0; i < 64; i++) {
        cout << rookMaskWithoutBorder[i];
        if (i < 63) {
            cout << ", ";
        }
    }
    cout << "}";

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
            while (k < i - i % 8 + 8) {
                moves |= 1ULL << k;
                if (blockers & 1ULL << k) break;
                k++;
            }
            values[i].push_back(moves);
        }
    }

    int cnt = 0;
    for (int i = 0; i < 64; i++) {
        cnt += keys[i].size();
    }

    fout << cnt << endl;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < keys[i].size(); j++) {
            fout << i << " " << keys[i][j] << " " << values[i][j] << endl;
        }
    }

    return 0;
}