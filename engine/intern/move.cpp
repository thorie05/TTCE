#include "chessboard.hpp"
#include "unmake_info.hpp"
#include "constants.hpp"
#include "move.hpp"
#include <array>
#include <iostream>
#include <tuple>

void Chessboard::move(const Move move) {
    /*
    moves a piece on the board
    */

    UnmakeInfo currentUnmakeInfo;
    currentUnmakeInfo.from = move.from;
    currentUnmakeInfo.to = move.to;

    // find moving piece and captured piece
    int movedPiece = mailbox[move.from];
    int capturedPiece = mailbox[move.to];

    currentUnmakeInfo.capturedPiece = capturedPiece;

    // move start piece and remove end piece on the bitboards
    bitboards[movedPiece] ^= 1ULL << move.from;
    bitboards[movedPiece] |= 1ULL << move.to;
    bitboards[capturedPiece] ^= 1ULL << move.to;

    // move start piece and remove end piece in the mailbox array
    mailbox[move.from] = EMPTY_SQUARE;
    mailbox[move.to] = movedPiece;

    // handle promotion
    if (move.promotion) {
        currentUnmakeInfo.promotion = true;

        bitboards[movedPiece] ^= 1ULL << move.to;
        bitboards[move.promotionPiece] |= 1ULL << move.to;
        mailbox[move.to] = move.promotionPiece;
    }

    // calculate new bitboards
    bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] 
        | bitboards[WHITE_BISHOP] | bitboards[WHITE_ROOK]
        | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];

    bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] 
        | bitboards[BLACK_BISHOP] | bitboards[BLACK_ROOK]
        | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];

    bitboards[PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];

    currentUnmakeInfo.halfmoveClock = halfmoveClock;

    // increment or reset halfmove clock
    halfmoveClock++;
    if (capturedPiece != EMPTY_SQUARE || movedPiece == WHITE_PAWN
        || movedPiece == BLACK_PAWN) {
        // if capture or pawn moved
        halfmoveClock = 0;
    }

    if (!isWhite(movedPiece)) {
        turnNumber++;
    }

    unmakeStack.push(currentUnmakeInfo);
}
