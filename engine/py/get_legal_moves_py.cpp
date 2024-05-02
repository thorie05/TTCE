#include "chessboard.hpp"
#include <vector>


std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>>
    Chessboard::getLegalMovesPy() {
    /*
    returns all legal moves on the current position
    */

    // generate legal moves
    std::vector<Move> legalMoves = getPseudoLegalMoves();
    std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>> 
        returnMoves;

    for (int i = 0; i < (int)legalMoves.size(); i++) {
        returnMoves.push_back(structToPyMove(legalMoves[i]));
    }

    return returnMoves;
}

