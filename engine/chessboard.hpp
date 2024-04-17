#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "position.hpp"
#include "magic_info.hpp"
#include <string>
#include <stack>
#include <tuple>
#include <vector>
#include <iostream>
#include <array>
#include <unordered_map>

typedef unsigned long long U64;
typedef unsigned short U16;


class Chessboard {
    private:
        std::string inputFen;
        Position board;
        MagicInfo magic;

        // engine intern methods

        std::vector<U16> getPseudoLegalMoves();

        void move(U16 move);

    public:
        // init
        Chessboard(const std::string& fen);

        // methods for the python module

        std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, 
            char>> getPseudoLegalMovesPy();

        std::tuple<std::vector<std::vector<char>>, char, bool, bool, bool, bool,
            std::tuple<int,int>, int, int> getBoardInfoPy();

        void movePy(std::tuple<int,int> startSquare, 
            std::tuple<int,int> endSquare, char promotion);
};

#endif