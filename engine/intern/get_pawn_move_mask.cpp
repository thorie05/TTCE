#include "chessboard.hpp"


U64 Chessboard::getPawnMoveMask(const int square) {
    /*
    returns move mask for the pawn on the given square
    */

    U64 moveMask = 0ULL;

    // calculate moving directions based on color
    int startRank = 1;
    int up = 8;
    int upWest = 7;
    int upEast = 9;
    if (mailbox[square] == BLACK_PAWN) {
        startRank = 6;
        up = -8;
        upWest = -9;
        upEast = -7;
    }

    if (!(bitboards[PIECES] & 1ULL << (square + up))) {
        moveMask |= 1ULL << (square + up);
        if (square / 8 == startRank
            && !(bitboards[PIECES] & 1ULL << (square + 2 * up))) {
        moveMask |= 1ULL << (square + 2 * up);
        }
    }
    if (bitboards[PIECES] & 1ULL << (square + upWest) && square % 8 - 1 >= 0) {
        moveMask |= 1ULL << (square + upWest);
    }
    if (bitboards[PIECES] & 1ULL << (square + upEast) && square % 8 + 1 < 8) {
        moveMask |= 1ULL << (square + upEast);
    }

    return moveMask;
}
