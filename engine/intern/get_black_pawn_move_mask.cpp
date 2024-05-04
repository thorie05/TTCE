#include "chessboard.hpp"


U64 Chessboard::getBlackPawnMoveMask(const int square) {
    /*
    returns move mask for a black pawn on the given square
    */

    U64 key = (bitboards[PIECES] & BLACK_PAWN_MASK[square]);
    int doublePushPos = std::max(0, square - 16);
    key >>= std::max(0, square - 9);
    key |= ((key & 1ULL << doublePushPos) >> doublePushPos) << 3;

    return BLACK_PAWN_LOOKUP[square * 16 + key];
}
