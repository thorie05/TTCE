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

    // set unmake info
    UnmakeInfo currentUnmakeInfo;
    currentUnmakeInfo.from = move.from;
    currentUnmakeInfo.to = move.to;
    currentUnmakeInfo.whiteCastleKingside = whiteCastleKingside;
    currentUnmakeInfo.whiteCastleQueenside = whiteCastleQueenside;
    currentUnmakeInfo.blackCastleKingside = blackCastleKingside;
    currentUnmakeInfo.blackCastleQueenside = blackCastleQueenside;
    currentUnmakeInfo.halfmoveClock = halfmoveClock;

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

    // handle castling with castling rights and en passant
    if (isWhite(movedPiece)) {
        if (movedPiece == WHITE_KING) {
            // remove castling rights for both sides if king moved
            whiteCastleKingside = false;
            whiteCastleQueenside = false;

            // white castled kingside
            if (move.from == 4 && move.to == 6) {
                bitboards[WHITE_ROOK] ^= 1ULL << 7;
                bitboards[WHITE_ROOK] |= 1ULL << 5;
                mailbox[7] = EMPTY_SQUARE;
                mailbox[5] = WHITE_ROOK;
            }
            // white castled queenside
            if (move.from == 4 && move.to == 2) {
                bitboards[WHITE_ROOK] ^= 1ULL << 0;
                bitboards[WHITE_ROOK] |= 1ULL << 3;
                mailbox[0] = EMPTY_SQUARE;
                mailbox[3] = WHITE_ROOK;
            }
        }
        // if rook moves remove castling right for that side
        else if (movedPiece == WHITE_ROOK && move.from == 0) {
            whiteCastleQueenside = false;
        }
        else if (movedPiece == WHITE_ROOK && move.from == 7) {
            whiteCastleKingside = false;
        }

        // if white captures black rook remove castling right for that side
        if (move.to == 56) {
            blackCastleQueenside = false;
        }
        if (move.to == 63) {
            blackCastleKingside = false;
        }

        // capture en passant
        if (move.enPassant) {
            bitboards[BLACK_PAWN] ^= 1ULL << enPassantSquare;
            mailbox[enPassantSquare] = EMPTY_SQUARE;

            currentUnmakeInfo.enPassant = true;
        }

        // add en passant square if double pawn push
        enPassantSquare = NONE_SQUARE;
        if (movedPiece == WHITE_PAWN
            && move.from / 8 == 1 && move.to / 8 == 3) {
                enPassantSquare = move.to;
        }
    }
    else {
        if (movedPiece == BLACK_KING) {
            // remove castling rights for both sides if king moved
            blackCastleKingside = false;
            blackCastleQueenside = false;

            // black castled kingside
            if (move.from == 60 && move.to == 62) {
                bitboards[BLACK_ROOK] ^= 1ULL << 63;
                bitboards[BLACK_ROOK] |= 1ULL << 61;
                mailbox[63] = EMPTY_SQUARE;
                mailbox[61] = BLACK_ROOK;
            }
            // black castled queenside
            if (move.from == 60 && move.to == 58) {
                bitboards[BLACK_ROOK] ^= 1ULL << 56;
                bitboards[BLACK_ROOK] |= 1ULL << 59;
                mailbox[56] = EMPTY_SQUARE;
                mailbox[59] = BLACK_ROOK;
            }
        }
        // if rook moves remove castling right for that side
        else if (movedPiece == BLACK_ROOK && move.from == 56) {
            blackCastleQueenside = false;
        }
        else if (movedPiece == BLACK_ROOK && move.from == 63) {
            blackCastleKingside = false;
        }

        // if black captures white rook remove castling right for that side
        if (move.to == 0) {
            whiteCastleQueenside = false;
        }
        if (move.to == 7) {
            whiteCastleKingside = false;
        }

        // add en passant square if double pawn push
        enPassantSquare = NONE_SQUARE;
        if (movedPiece == BLACK_PAWN
            && move.from / 8 == 6 && move.to / 8 == 4) {
                enPassantSquare = move.to;
        }

        // capture en passant
        if (move.enPassant) {
            bitboards[WHITE_PAWN] ^= 1ULL << (move.to + 8);
            mailbox[move.to + 8] = EMPTY_SQUARE;

            currentUnmakeInfo.enPassant = true;
        }
    }

    // calculate new bitboards
    bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] 
        | bitboards[WHITE_BISHOP] | bitboards[WHITE_ROOK]
        | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];

    bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] 
        | bitboards[BLACK_BISHOP] | bitboards[BLACK_ROOK]
        | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];

    bitboards[PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];

    // increment halfmove clock
    halfmoveClock++;
    if (capturedPiece != EMPTY_SQUARE || movedPiece == WHITE_PAWN
        || movedPiece == BLACK_PAWN) {
        // if capture or pawn moved reset halfmove clock
        halfmoveClock = 0;
    }

    if (!isWhite(movedPiece)) {
        turnNumber++;
    }

    unmakeStack.push(currentUnmakeInfo);
}
