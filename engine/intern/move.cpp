#include "chessboard.hpp"
#include "constants.hpp"
#include <array>
#include <iostream>
#include <tuple>

void Chessboard::move(U16 move) {
    /*
    moves a piece on the board
    */

    // apply move bitmask
    U16 start = move & 63; // first 6 bits represent the start square
    U16 end = (move & 4032) >> 6; // next 6 bits represent the end square
    U16 promotion = (move & 64512) >> 12; // last 4 bits contain promotion info

    // find moving piece and potentially captured piece
    int startPiece = mailbox[start];
    int endPiece = mailbox[end];

    // move start piece and remove end piece on the bitboards
    bitboards[startPiece] ^= 1ULL << start;
    bitboards[startPiece] |= 1ULL << end;
    bitboards[endPiece] ^= 1ULL << end;

    // move start piece and remove end piece in the mailbox array
    mailbox[start] = EMPTY_SQUARE;
    mailbox[end] = startPiece;

    // handle promotion
    if ((startPiece == WHITE_PAWN && end / 8 == 7)
        || (startPiece == BLACK_PAWN && end / 8 == 0)) {

        int promotionPiece;

        switch (promotion | (startPiece == WHITE_PAWN ? 0 : 1) << 2) {
            case 0: // white promotes to queen
                promotionPiece = WHITE_QUEEN;
                break;
            case 1: // white promotes to rook
                promotionPiece = WHITE_ROOK;
                break;
            case 2: // white promotes to bishop
                promotionPiece = WHITE_BISHOP;
                break;
            case 3: // white promotes to knight
                promotionPiece = WHITE_KNIGHT;
                break;
            case 4: // black promotes to queen
                promotionPiece = BLACK_QUEEN;
                break;
            case 5: // black promotes to rook
                promotionPiece = BLACK_ROOK;
                break;
            case 6: // black promotes to bishop
                promotionPiece = BLACK_BISHOP;
                break;
            case 7: // black promotes to knight
                promotionPiece = BLACK_KNIGHT;
                break;
        }

        bitboards[startPiece] ^= 1ULL << end;
        bitboards[promotionPiece] |= 1ULL << end;
        mailbox[end] = promotionPiece;
    }

    // calculate new bitboards
    bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] 
        | bitboards[WHITE_BISHOP] | bitboards[WHITE_ROOK]
        | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];

    bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] 
        | bitboards[BLACK_BISHOP] | bitboards[BLACK_ROOK]
        | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];

    bitboards[PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];
}
