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
            bitboards[WHITE_PAWN] |= 1ULL << last.from;
        }
        else {
            mailbox[last.from] = BLACK_PAWN;
            bitboards[BLACK_PAWN] |= 1ULL << last.from;
        }
    }

    // handle castling
    if (movedPiece == WHITE_KING) {
        // white castled kingside
        if (last.from == 4 && last.to == 6) {
            bitboards[WHITE_ROOK] ^= 1ULL << 5;
            bitboards[WHITE_ROOK] |= 1ULL << 7;
            mailbox[5] = EMPTY_SQUARE;
            mailbox[7] = WHITE_ROOK;
        }
        // white castled queenside
        if (last.from == 4 && last.to == 2) {
            bitboards[WHITE_ROOK] ^= 1ULL << 3;
            bitboards[WHITE_ROOK] |= 1ULL << 0;
            mailbox[3] = EMPTY_SQUARE;
            mailbox[0] = WHITE_ROOK;
        }
    }
    else if (movedPiece == BLACK_KING) {
        // black castled kingside
        if (last.from == 60 && last.to == 62) {
            bitboards[BLACK_ROOK] ^= 1ULL << 61;
            bitboards[BLACK_ROOK] |= 1ULL << 63;
            mailbox[61] = EMPTY_SQUARE;
            mailbox[63] = BLACK_ROOK;
        }
        // black castled queenside
        if (last.from == 60 && last.to == 58) {
            bitboards[BLACK_ROOK] ^= 1ULL << 59;
            bitboards[BLACK_ROOK] |= 1ULL << 56;
            mailbox[59] = EMPTY_SQUARE;
            mailbox[56] = BLACK_ROOK;
        }
    }
    // handle en passant
    else if (last.enPassant) {
        if (movedPiece == WHITE_PAWN) {
            bitboards[BLACK_PAWN] |= 1ULL << (last.to - 8);
            mailbox[last.to - 8] = BLACK_PAWN;
        }
        else {
            bitboards[WHITE_PAWN] |= 1ULL << (last.to + 8);
            mailbox[last.to + 8] = WHITE_PAWN;
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

    // restore castling rights
    whiteCastleKingside = last.whiteCastleKingside;
    whiteCastleQueenside = last.whiteCastleQueenside;
    blackCastleKingside = last.blackCastleKingside;
    blackCastleQueenside = last.blackCastleQueenside;

    halfmoveClock = last.halfmoveClock;

    if (!isWhite(movedPiece)) {
        turnNumber--;
    }
}
