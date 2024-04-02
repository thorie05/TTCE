#include "chessboard.hpp"
#include <array>
#include <iostream>
#include <tuple>

void Chessboard::pushMove(U16 move) {
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

void Chessboard::pushMove(std::tuple<int,int> startSquare, 
    std::tuple<int,int> endSquare, char promotion = 'q') {
    // moves a piece on the board

    // translate to move tuple U16
    U16 move = 0;
    move |= (std::get<1>(startSquare) * 8 + std::get<0>(startSquare));
    move |= ((std::get<1>(endSquare) * 8 + std::get<0>(endSquare))<<6);
    switch (promotion) {
        // queen is 0
        case 'r':
            move |= 4096; // 1 shifted 12 bits
            break;
        case 'b':
            move |= 8192; // 2 shifted 12 bits
            break;
        case 'n':
            move |= 12288; // 3 shifted 12 bits
            break;
    }

    Chessboard::pushMove(move);
}