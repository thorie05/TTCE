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


U64 generateMoves(int square, const U64& blockers, 
    const array<int, 4>& directions) {
    /*
    generates the valid moves of a sliding piece moving according to the 
    directions array and standing on square with the given blockers
    */

    U64 possibleMoves = 0ULL; // bitboard representing all possible moves

    // move in the four given directions
    for (int i = 0; i < 4; i++) {
        int s = square;
        // move until blocking piece or wall is encountered
        while (s >= 0 && s < 64) {
            possibleMoves |= 1ULL << s;
            if (blockers & 1ULL << s) {
                break;
            }
            if (s % 8 == 0 && (s + directions[i]) % 8 == 7) {
                break;
            }
            if (s % 8 == 7 && (s + directions[i]) % 8 == 0) {
                break;
            }
            s += directions[i];
        }
    }

    // remove square the piece is standing on
    possibleMoves ^= 1ULL << square;

    return possibleMoves;
}


int main() {
    // generate piece masks

    array<U64, 64> bishopPreMasks;
    array<U64, 64> rookPreMasks;
    array<U64, 64> bishopPostMasks;
    array<U64, 64> rookPostMasks;

    int a = 0;
    int b = 0;

    for (int i = 0; i < 64; i++) {
        bishopPostMasks[i] = generateMoves(i, 0ULL, {7, 9, -7, -9});
        rookPostMasks[i] = generateMoves(i, 0ULL, {-1, 8, 1, -8});

        // remove last square in every direction for piece mask since there
        // is no difference if it is there or not
        U64 relevantSquares = 0x7e7e7e7e7e7e00ULL; // relevant squares are in 
                                                   // the middle
        // add border to relevant squares if piece stands on that border
        if (0xffULL & 1ULL << i) { // bottom
            relevantSquares |= 0x7eULL;
        }
        if (0x8080808080808080ULL & 1ULL << i) { // right
            relevantSquares |= 0x80808080808000ULL;
        }
        if (0xff00000000000000ULL & 1ULL << i) { // upper
            relevantSquares |= 0x7e00000000000000ULL;
        }
        if (0x101010101010101ULL & 1ULL << i) { // left
            relevantSquares |= 0x1010101010100ULL;
        }
        bishopPreMasks[i] = bishopPostMasks[i] & relevantSquares;
        rookPreMasks[i] = rookPostMasks[i] & relevantSquares;
    }

    // generate key value pairs

    array<vector<U64>, 64> bishopKeys;
    array<vector<U64>, 64> bishopValues;

    array<vector<U64>, 64> rookKeys;
    array<vector<U64>, 64> rookValues;

    for (int sq = 0; sq < 64; sq++) { // iterate over every square
        U64 bishopMask = bishopPreMasks[sq];
        U64 rookMask = rookPreMasks[sq];

        vector<int> blockerPositionsBishop; // store the index of every blocker
        vector<int> blockerPositionsRook;
        for (int i = 0; i < 64; i++) {
            if (bishopMask & 1ULL << i) {
                blockerPositionsBishop.push_back(i);
            }
            if (rookMask & 1ULL << i) {
                blockerPositionsRook.push_back(i);
            }
        }

        // iterate over all combinations of set bits for every blocker 
        // position to get all possible blocker bitboards for every square

        // bishops
        for (int i = 0; i < 1 << blockerPositionsBishop.size(); i++) {
            U64 blockersBishop = 0ULL;
            // iterate through the blocker positions
            for (int j = 0; j < blockerPositionsBishop.size(); j++) {
                if (i & 1ULL << j) { // bits get pushed in the right places
                    blockersBishop |= 1ULL << blockerPositionsBishop[j];
                }
            }
            bishopKeys[sq].push_back(blockersBishop);
        }

        // rooks
        for (int i = 0; i < 1 << blockerPositionsRook.size(); i++) {
            U64 blockersRook = 0ULL;
            for (int j = 0; j < blockerPositionsRook.size(); j++) {
                if (i & 1ULL << j) {
                    blockersRook |= 1ULL << blockerPositionsRook[j];
                }
            }
            rookKeys[sq].push_back(blockersRook);
        }
    }
    // after the loop the key arrays contains every possible combination of
    // blocking pieces for every square

    // generate possible moves for every combination of blockers
    for (int i = 0; i < 64; i++) {
        bishopValues[i].resize(bishopKeys[i].size());
        for (int j = 0; j < bishopKeys[i].size(); j++) {
            bishopValues[i][j] = generateMoves(i, bishopKeys[i][j], 
                {7, 9, -7, -9});
        }
        rookValues[i].resize(rookKeys[i].size());
        for (int j = 0; j < rookKeys[i].size(); j++) {
            rookValues[i][j] = generateMoves(i, rookKeys[i][j], {-1, 8, 1, -8});
        }
    }
    // values arrays cnow ontain possible moves for every position in keys

    // count number of lines
    int cntBishops = 0;
    int cntRooks = 0;
    for (int i = 0; i < 64; i++) {
        cntBishops += bishopKeys[i].size();
        cntRooks += rookKeys[i].size();
    }

    // write key value pairs for bishops into a file
    ofstream foutBishops("key_value_pairs_bishops.txt");
    foutBishops << cntBishops << endl;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < bishopKeys[i].size(); j++) {
            foutBishops << i << " " << bishopKeys[i][j] << " " 
                << bishopValues[i][j] << endl;
        }
    }
    foutBishops.close();

    // write key value pairs for rooks into a file
    ofstream foutRooks("key_value_pairs_rooks.txt");
    foutRooks << cntRooks << endl;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < rookKeys[i].size(); j++) {
            foutRooks << i << " " << rookKeys[i][j] << " " << rookValues[i][j]
                << endl;
        }
    }
    foutRooks.close();

    // write post masks to file
    ofstream foutMasks("masks.txt");
    for (int i = 0; i < 64; i++) {
        foutMasks << bishopPostMasks[i] << " ";
    }
    foutMasks << endl;
    for (int i = 0; i < 64; i++) {
        foutMasks << rookPostMasks[i] << " ";
    }

    return 0;
}
