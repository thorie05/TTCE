#include "chessboard.hpp"


U64 Chessboard::getWhitePawnMoveMask(const int square) {
    /*
    returns move mask for a white pawn on the given square
    */

    U64 key = (bitboards[PIECES] & WHITE_PAWN_MASK[square]) >> (square + 7);
    U64 doublePushBit = key & 1ULL << 9;
    key ^= doublePushBit | (doublePushBit >> 6);

    return WHITE_PAWN_LOOKUP[square * 16 + key];
}
