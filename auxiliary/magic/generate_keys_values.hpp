#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;


U64 getMoves(int square, const U64& blockers, 
    const array<int, 4>& directions) {
    /*
    generates the valid moves of a sliding piece moving standing on square
    according to the given blockers and directions array
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


void getMasksAndLookupTables(array<U64, 64>& bishopMasks,
    array<U64, 64>& rookMasks,
    array<unordered_map<U64, U64>, 64>& bishopLookupTable,
    array<unordered_map<U64, U64>, 64>& rookLookupTable) {
    /*
    calculates the relevant occupancy masks and the lookup tables for bishops
    and rooks
    */

    // generate relevant occupancy masks

    for (int sq = 0; sq < 64; sq++) {
        // post masks
        bishopMasks[sq] = getMoves(sq, 0ULL, {7, 9, -7, -9});
        rookMasks[sq] = getMoves(sq, 0ULL, {-1, 8, 1, -8});

        // remove last square in every direction to get pre mask

        U64 relevantSquares = 0x7e7e7e7e7e7e00ULL; // middle squares
        // add border to relevant squares if piece stands on that border
        if (0xffULL & 1ULL << sq) { // bottom
            relevantSquares |= 0x7eULL;
        }
        if (0x8080808080808080ULL & 1ULL << sq) { // right
            relevantSquares |= 0x80808080808000ULL;
        }
        if (0xff00000000000000ULL & 1ULL << sq) { // upper
            relevantSquares |= 0x7e00000000000000ULL;
        }
        if (0x101010101010101ULL & 1ULL << sq) { // left
            relevantSquares |= 0x1010101010100ULL;
        }

        bishopMasks[sq] &= relevantSquares;
        rookMasks[sq] &= relevantSquares;
    }

    // generate lookup tables

    for (int sq = 0; sq < 64; sq++) { // loop over every square
        U64 bishopMask = bishopMasks[sq];
        U64 rookMask = rookMasks[sq];

        vector<int> bishopBlockerPositions; // store the indices of all relevant
        vector<int> rookBlockerPositions; // blockers
        for (int i = 0; i < 64; i++) {
            if (bishopMask & 1ULL << i) {
                bishopBlockerPositions.push_back(i);
            }
            if (rookMask & 1ULL << i) {
                rookBlockerPositions.push_back(i);
            }
        }

        // iterate over all combinations of set bits on the relevant blocker 
        // indices to get all possible lookup keys

        // bishops
        for (int i = 0; i < 1 << bishopBlockerPositions.size(); i++) {
            U64 key = 0ULL;
            for (int j = 0; j < bishopBlockerPositions.size(); j++) {
                if (i & 1ULL << j) { // push bits into the right places
                    key |= 1ULL << bishopBlockerPositions[j];
                }
            }
            bishopLookupTable[sq][key] = getMoves(sq, key, {7, 9, -7, -9});
        }

        // rooks
        for (int i = 0; i < 1 << rookBlockerPositions.size(); i++) {
            U64 key = 0ULL;
            for (int j = 0; j < rookBlockerPositions.size(); j++) {
                if (i & 1ULL << j) { // push bits into the right places
                    key |= 1ULL << rookBlockerPositions[j];
                }
            }
            rookLookupTable[sq][key] = getMoves(sq, key, {-1, 8, 1, -8});
        }
    }
}
