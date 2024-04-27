#include "chessboard.hpp"
#include <iostream>
#include <tuple>

std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>> 
    Chessboard::getLegalMovesPy() {
    /*
    returns all legal moves on the current position
    */

    // generate legal moves in short move format
    std::vector<U16> legalMoves = getLegalMoves();
    std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>> 
        returnMoves;

    for (int i = 0; i < (int)legalMoves.size(); i++) {
        // read values from short move format
        U16 move = legalMoves[i];
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
