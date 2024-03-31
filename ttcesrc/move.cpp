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

    std::array<U64*,12> bitboards = {
        &board.whitePawns,
        &board.whiteKnights,
        &board.whiteBishops,
        &board.whiteRooks,
        &board.whiteQueens,
        &board.whiteKing,
        &board.blackPawns,
        &board.blackKnights,
        &board.blackBishops,
        &board.blackRooks,
        &board.blackQueens,
        &board.blackKing,
    };

    // adjust bitboards
    bool foundStart = false;
    bool foundEnd = false;
    for (int i = 0; i < 12; i++) {
        if (*bitboards[i] & 1ULL<<end) {
            *bitboards[i] ^= 1ULL<<end;
            foundEnd = true;
        }
        if (*bitboards[i] & 1ULL<<start) {
            *bitboards[i] ^= 1ULL<<start;
            *bitboards[i] |= 1ULL<<end;
            foundStart = true;
        }
        if (foundEnd && foundStart) {
            break;
        }
    }

    // calculate new pieces bitboards
    board.whitePieces = board.whitePawns | board.whiteKnights 
        | board.whiteBishops | board.whiteRooks | board.whiteQueens 
        | board.whiteKing;

    board.blackPieces = board.blackPawns | board.blackKnights 
        | board.blackBishops | board.blackRooks | board.blackQueens 
        | board.blackKing;

    board.pieces = board.whitePieces | board.blackPieces;
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

    // call move
    Chessboard::pushMove(move);
}