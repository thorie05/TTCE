#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <array>

typedef unsigned long long U64;


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

constexpr std::array<U64, 64> KNIGHT_LOOKUP = {
    0x20400, 0x50800, 0xa1100, 0x142200, 0x284400, 0x508800, 0xa01000, 0x402000,
    0x2040004, 0x5080008, 0xa110011, 0x14220022, 0x28440044, 0x50880088,
    0xa0100010, 0x40200020, 0x204000402, 0x508000805, 0xa1100110a, 0x1422002214,
    0x2844004428, 0x5088008850, 0xa0100010a0, 0x4020002040, 0x20400040200,
    0x50800080500, 0xa1100110a00, 0x142200221400, 0x284400442800,
    0x508800885000, 0xa0100010a000, 0x402000204000, 0x2040004020000,
    0x5080008050000, 0xa1100110a0000, 0x14220022140000, 0x28440044280000,
    0x50880088500000, 0xa0100010a00000, 0x40200020400000, 0x204000402000000,
    0x508000805000000, 0xa1100110a000000, 0x1422002214000000,
    0x2844004428000000, 0x5088008850000000, 0xa0100010a0000000,
    0x4020002040000000, 0x400040200000000, 0x800080500000000,
    0x1100110a00000000, 0x2200221400000000, 0x4400442800000000,
    0x8800885000000000, 0x100010a000000000, 0x2000204000000000, 0x4020000000000,
    0x8050000000000, 0x110a0000000000, 0x22140000000000, 0x44280000000000,
    0x88500000000000, 0x10a00000000000, 0x20400000000000
};

constexpr std::array<U64, 64> KING_LOOKUP = {
    0x302, 0x705, 0xe0a, 0x1c14, 0x3828, 0x7050, 0xe0a0, 0xc040, 0x30203,
    0x70507, 0xe0a0e, 0x1c141c, 0x382838, 0x705070, 0xe0a0e0, 0xc040c0,
    0x3020300, 0x7050700, 0xe0a0e00, 0x1c141c00, 0x38283800, 0x70507000,
    0xe0a0e000, 0xc040c000, 0x302030000, 0x705070000, 0xe0a0e0000, 0x1c141c0000,
    0x3828380000, 0x7050700000, 0xe0a0e00000, 0xc040c00000, 0x30203000000,
    0x70507000000, 0xe0a0e000000, 0x1c141c000000, 0x382838000000,
    0x705070000000, 0xe0a0e0000000, 0xc040c0000000, 0x3020300000000,
    0x7050700000000, 0xe0a0e00000000, 0x1c141c00000000, 0x38283800000000,
    0x70507000000000, 0xe0a0e000000000, 0xc040c000000000, 0x302030000000000,
    0x705070000000000, 0xe0a0e0000000000, 0x1c141c0000000000,
    0x3828380000000000, 0x7050700000000000, 0xe0a0e00000000000,
    0xc040c00000000000, 0x203000000000000, 0x507000000000000, 0xa0e000000000000,
    0x141c000000000000, 0x2838000000000000, 0x5070000000000000,
    0xa0e0000000000000, 0x40c0000000000000
};

#endif
