#include "chessboard.hpp"


void Chessboard::unmakeMove() {
    /*
    unmakes the last played move
    */

    if (unmakeStack.size() == 0) {
        return;
    }
    UnmakeInfo last = unmakeStack.top();
    unmakeStack.pop();

    // apply move bitmask
    U16 startSquare = last.move & 63;
    U16 endSquare = (last.move & 4032) >> 6;

    int movedPiece = mailbox[endSquare];

    // restore bitboards
    bitboards[movedPiece] ^= 1ULL << endSquare;
    bitboards[movedPiece] |= 1ULL << startSquare;
    bitboards[last.capturedPiece] |= 1ULL << endSquare;

    // restore mailbox array
    mailbox[startSquare] = movedPiece;
    mailbox[endSquare] = last.capturedPiece;

    // handle promotion
    if (last.promotion) {
        bitboards[movedPiece] ^= 1ULL << startSquare;
        if (isWhite(movedPiece)) {
            mailbox[startSquare] = WHITE_PAWN;
        }
        else {
            mailbox[startSquare] = BLACK_PAWN;
        }
    }

    // recalculate other bitboards
    bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] 
        | bitboards[WHITE_BISHOP] | bitboards[WHITE_ROOK]
        | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];

    bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] 
        | bitboards[BLACK_BISHOP] | bitboards[BLACK_ROOK]
        | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];

    bitboards[PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];
}
