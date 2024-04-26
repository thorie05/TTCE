#ifndef BOARD_INFO_HPP
#define BOARD_INFO_HPP

#include <array>
#include <tuple>

struct BoardInfo {
    std::array<std::array<char, 8>, 8> board;
    char turn;
    std::tuple<bool, bool, bool, bool> castlingRights;
    std::tuple<int, int> enPassantSquare;
    int halfmoveClock;
    int turnNumber;
};

#endif
