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

    int movedPiece = mailbox[last.to];

    // restore bitboards
    bitboards[movedPiece] ^= 1ULL << last.to;
    bitboards[movedPiece] |= 1ULL << last.from;
    bitboards[last.capturedPiece] |= 1ULL << last.to;

    // restore mailbox array
    mailbox[last.from] = movedPiece;
    mailbox[last.to] = last.capturedPiece;

    // handle promotion
    if (last.promotion) {
        bitboards[movedPiece] ^= 1ULL << last.from;
        if (isWhite(movedPiece)) {
            mailbox[last.from] = WHITE_PAWN;
        }
        else {
            mailbox[last.from] = BLACK_PAWN;
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
