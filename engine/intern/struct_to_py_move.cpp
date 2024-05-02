#include "chessboard.hpp"
#include "move.hpp"
#include "chessboard.hpp"
#include <tuple>


std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>
    Chessboard::structToPyMove(const Move move) {
    /*
    translates Move struct to python move
    */

    // transfrom start and end square to coordinates
    std::tuple<int, int> startTuple = std::make_tuple(move.from % 8,
        move.from / 8);
    std::tuple<int, int> endTuple = std::make_tuple(move.to % 8, move.to / 8);

    // translate promotion piece
    char promotionChar;
    switch (move.promotionPiece) {
        case EMPTY_SQUARE:
            promotionChar = ' ';
            break;
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            promotionChar = 'n';
            break;
        case WHITE_BISHOP:
        case BLACK_BISHOP:
            promotionChar = 'b';
            break;
        case WHITE_ROOK:
        case BLACK_ROOK:
            promotionChar = 'r';
            break;
        case WHITE_QUEEN:
        case BLACK_QUEEN:
            promotionChar = 'q';
            break;
    }

    return std::make_tuple(startTuple, endTuple, promotionChar);
}
