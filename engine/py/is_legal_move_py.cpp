#include "chessboard.hpp"


bool Chessboard::isLegalMovePy(std::tuple<int, int> startSquare,
    std::tuple<int, int> endSquare, char promotion) {
    /*
    returns if the given move is legal on the current position
    */

    return isLegalMove(pyMoveToU16(startSquare, endSquare, promotion));
}

