#include "chessboard.hpp"


U64 Chessboard::getBishopMoveMask(int square) {
    /*
    returns move mask for the bishop on the given square
    */

    // calculate lookup key
    U64 key = bitboards[PIECES] & magic.bishopMasks[square];
    key *= magic.bishopMagicNumbers[square];
    key >>= magic.bishopShifts[square];
    key += magic.bishopLookupIndex[square];

    // get moves using that key
    U64 moveMask = magic.bishopLookup[key];

    return moveMask;
}
