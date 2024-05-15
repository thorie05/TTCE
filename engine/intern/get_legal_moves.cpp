#include "chessboard.hpp"
#include "move.hpp"
#include <vector>


std::vector<Move> Chessboard::getLegalMoves() {
    /*
    returns all legal moves on the current position
    */

    std::vector<Move> pseudoLegalMoves = getPseudoLegalMoves();
    std::vector<Move> legalMoves;

    for (int i = 0; i < (int)pseudoLegalMoves.size(); i++) {
        if (isLegalMove(pseudoLegalMoves[i])) {
            legalMoves.push_back(pseudoLegalMoves[i]);
        }
    }

    return legalMoves;
}
