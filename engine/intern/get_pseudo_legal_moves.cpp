#include "chessboard.hpp"
#include "constants.hpp"
#include <iostream>
#include <tuple>

std::vector<U16> Chessboard::getPseudoLegalMoves() {
    std::vector<U16> pseudoLegalMoves;
    // returns all pseudo legal moves

    if (board.turn) { // whites turn
        for (int i = 0; i < 64; i++) {
            int piece = board.mailbox[i];

            switch (piece) {
                case WHITE_PAWN:
                    if (!(board.bitboards[PIECES] & 1ULL<<(i + 8))) {
                        // move one square forward
                        pseudoLegalMoves.push_back(i | (i + 8) << 6);
                        if (!(board.bitboards[PIECES] & 1ULL<<(i + 16)) 
                            && i >= 8 && i <= 15) {
                            // move two squares forward
                            pseudoLegalMoves.push_back(i | (i + 16) << 6);
                        }
                    }
                    break;
                case WHITE_BISHOP:
                    break;
            }
        }
    }
    else { // blacks turn

    }

    return pseudoLegalMoves;
}
