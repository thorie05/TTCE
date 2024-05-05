#include "chessboard.hpp"


U64 Chessboard::getBlackPawnMoveMask(const int square) {
    /*
    returns move mask for a black pawn on the given square
    */

    U64 key = (bitboards[PIECES] & BLACK_PAWN_MASK[square]) << (70 - square);
    U64 doublePushBit = key & 1ULL << 54;
    key ^= doublePushBit | (doublePushBit << 6);
    key >>= 60;

    return BLACK_PAWN_LOOKUP[square * 16 + key];
}
