#include "chessboard.hpp"
#include "constants.hpp"
#include <array>
#include <iostream>
#include <tuple>

void Chessboard::move(U16 move) {
    // moves a piece on the board

    // apply move bitmask
    U16 start = move & 63; // first 6 bits represent the start square
    U16 end = (move & 4032) >> 6; // next 6 bits represent the end square
    // U16 promotion = (move & 64512) >> 12; // last 4 bits contain promotion info

    // find moving piece and potentially captured piece
    int startPiece = board.mailbox[start];
    int endPiece = board.mailbox[end];

    // move start piece and remove end piece on the bitboards
    board.bitboards[startPiece] ^= 1ULL<<start;
    board.bitboards[startPiece] |= 1ULL<<end;
    board.bitboards[endPiece] ^= 1ULL<<end;

    // move start piece and remove end piece in the mailbox array
    board.mailbox[start] = EMPTY_SQUARE;
    board.mailbox[end] = startPiece;

    // calculate new bitboards
    board.bitboards[12] = board.bitboards[0] | board.bitboards[1] 
        | board.bitboards[2] | board.bitboards[3] | board.bitboards[4] 
        | board.bitboards[5];

    board.bitboards[13] = board.bitboards[6] | board.bitboards[7] 
        | board.bitboards[8] | board.bitboards[9] | board.bitboards[10] 
        | board.bitboards[11];

    board.bitboards[14] = board.bitboards[12] | board.bitboards[13];
}
