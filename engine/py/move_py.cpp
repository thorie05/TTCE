#include "chessboard.hpp"
#include <array>
#include <iostream>
#include <tuple>


void Chessboard::movePy(const std::tuple<int, int>& startSquare, 
    const std::tuple<int, int>& endSquare, char promotionPiece = 'q') {
    /*
    moves a piece on the board
    */

    Move move = pyMoveToStruct(startSquare, endSquare, promotionPiece);

    Chessboard::move(move);
}
