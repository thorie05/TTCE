#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

// fen string of starting chess position
constexpr std::string_view DEFAULT_FEN = 
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

// constants denote index in the bitboards array and value in the mailbox array
constexpr int WHITE_PAWN = 0;
constexpr int WHITE_KNIGHT = 1;
constexpr int WHITE_BISHOP = 2;
constexpr int WHITE_ROOK = 3;
constexpr int WHITE_QUEEN = 4;
constexpr int WHITE_KING = 5;
constexpr int BLACK_PAWN = 6;
constexpr int BLACK_KNIGHT = 7;
constexpr int BLACK_BISHOP = 8;
constexpr int BLACK_ROOK = 9;
constexpr int BLACK_QUEEN = 10;
constexpr int BLACK_KING = 11;

constexpr int WHITE_PIECES = 12;
constexpr int BLACK_PIECES = 13;
constexpr int PIECES = 14;

constexpr int EMPTY_SQUARE = 15;

#endif
