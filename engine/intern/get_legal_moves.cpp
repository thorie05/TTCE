#include "chessboard.hpp"
#include <vector>


std::vector<U16> Chessboard::getLegalMoves() {
    /*
    returns all legal moves on the current position
    */

    std::vector<U16> pseudoLegalMoves = getPseudoLegalMoves();
    std::vector<U16> legalMoves = getPseudoLegalMoves();

    for (int i = 0; i < (int)pseudoLegalMoves.size(); i++) {
        if (isLegalMove(pseudoLegalMoves[i])) {
            legalMoves.push_back(pseudoLegalMoves[i]);
        }
    }

    return legalMoves;
}
