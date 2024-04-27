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
    // U16 promotion = (move & 64512) >> 12; // last 4 bits contain promotion info

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

    // calculate new bitboards
    bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] 
        | bitboards[WHITE_BISHOP] | bitboards[WHITE_ROOK]
        | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];

    bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] 
        | bitboards[BLACK_BISHOP] | bitboards[BLACK_ROOK]
        | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];

    bitboards[PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];
}
