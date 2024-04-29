#include "chessboard.hpp"
#include <array>
#include <iostream>
#include <tuple>


void Chessboard::movePy(std::tuple<int,int> startSquare, 
    std::tuple<int,int> endSquare, char promotion = 'q') {
    /*
    moves a piece on the board
    */

    U16 move = pyMoveToU16(startSquare, endSquare, promotion);

    Chessboard::move(move);
}
