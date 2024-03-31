#include "chessboard.hpp"
#include <tuple>

std::vector<U16> Chessboard::getPseudoLegalMoves() {
    std::vector<U16> pseudoLegalMoves;
    // returns all pseudo legal moves

    if (board.turn) {
        for (int i = 0; i < 64; i++) {
            if (board.whitePawns & 1ULL<<i) {
                if (!(board.pieces & 1ULL<<(i + 8))) {
                    pseudoLegalMoves.push_back(i | (i + 8) << 6);
                    if (!(board.pieces & 1ULL<<(i + 16)) && i >= 8 && i <= 15) {
                        pseudoLegalMoves.push_back(i | (i + 16) << 6);
                    }
                }
            }
        }
    }
    else {

    }

    return pseudoLegalMoves;
}

std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>> 
    Chessboard::getPseudoLegalMovesPy() {
    // returns all pseudo legal moves

    // generate pseudo legal moves in short move format
    std::vector<U16> pseudoLegalMoves = getPseudoLegalMoves();
    std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>> 
        returnMoves;

    for (int i = 0; i < (int)pseudoLegalMoves.size(); i++) {
        // read values from short move format
        U16 move = pseudoLegalMoves[i];
        int start = move & 63;
        int end = (move & 4032) >> 6;
        int promotion = (move & 64512) >> 12;

        // transfrom start and end square to coordinates
        std::tuple<int, int> startTuple = std::make_tuple(start % 8, start / 8);
        std::tuple<int, int> endTuple = std::make_tuple(end % 8, end / 8);

        // translate promotion piece
        char promotionChar;
        switch (promotion) {
            case 0:
                promotionChar = 'q';
                break;
            case 1:
                promotionChar = 'r';
                break;
            case 2:
                promotionChar = 'b';
                break;
            case 3:
                promotionChar = 'n';
                break;
        }
        returnMoves.push_back(std::make_tuple(startTuple, endTuple, 
            promotionChar));
    }

    return returnMoves;
}