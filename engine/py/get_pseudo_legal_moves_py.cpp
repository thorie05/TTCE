#include "chessboard.hpp"
#include <iostream>
#include <tuple>

std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>> 
    Chessboard::getPseudoLegalMovesPy() {
    /*
    returns all pseudo legal moves on the current position
    */

    // generate pseudo legal moves
    std::vector<Move> pseudoLegalMoves = getPseudoLegalMoves();
    std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>> 
        returnMoves;

    for (int i = 0; i < (int)pseudoLegalMoves.size(); i++) {
        returnMoves.push_back(structToPyMove(pseudoLegalMoves[i]));
    }

    return returnMoves;
}
