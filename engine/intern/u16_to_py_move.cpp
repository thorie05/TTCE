#include "chessboard.hpp"
#include <tuple>


std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>
    Chessboard::U16toPyMove(const U16 move) {
    /*
    translates U16 to python move
    */

    int startSquare = move & 63;
    int endSquare = (move & 4032) >> 6;
    int promotion = (move & 64512) >> 12;

    // transfrom start and end square to coordinates
    std::tuple<int, int> startTuple = std::make_tuple(startSquare % 8,
        startSquare / 8);
    std::tuple<int, int> endTuple = std::make_tuple(endSquare % 8,
        endSquare / 8);

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

    return std::make_tuple(startTuple, endTuple, promotionChar);
}
