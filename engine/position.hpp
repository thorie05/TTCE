#ifndef POSITION_HPP
#define POSITION_HPP

#include <array>

typedef unsigned long long U64;

struct Position {
    // struct containing board position

    std::array<int, 64> mailbox;
    std::array<U64, 16> bitboards; // index 15 redundant

    bool turn;

    // castling rights
    bool whiteCastleKingside;
    bool whiteCastleQueenside;
    bool blackCastleKingside;
    bool blackCastleQueenside;

    int enPassantSquare;
    int halfmoveClock;
    int turnNumber;
};

#endif
