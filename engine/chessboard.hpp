#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "position.hpp"
#include "magic_data.hpp"
#include "board_info.hpp"
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
        MagicData magic;

        // engine intern methods

        std::vector<U16> getLegalMoves();

        void move(U16 move);

    public:
        Chessboard(const std::string& fen); // init

        // methods for the python module

        std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, 
            char>> getLegalMovesPy();

        BoardInfo getBoardInfoPy();

        void movePy(std::tuple<int,int> startSquare, 
            std::tuple<int,int> endSquare, char promotion);
};

#endif