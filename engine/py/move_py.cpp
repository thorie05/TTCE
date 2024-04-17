#include "chessboard.hpp"
#include <array>
#include <iostream>
#include <tuple>

void Chessboard::movePy(std::tuple<int,int> startSquare, 
    std::tuple<int,int> endSquare, char promotion = 'q') {
    // moves a piece on the board

    // translate move tuple to U16
    U16 move = 0;
    move |= (std::get<1>(startSquare) * 8 + std::get<0>(startSquare));
    move |= ((std::get<1>(endSquare) * 8 + std::get<0>(endSquare))<<6);
    switch (promotion) {
        // queen is 0
        case 'r':
            move |= 1 << 12; // 1 shifted 12 bits
            break;
        case 'b':
            move |= 2 << 12; // 2 shifted 12 bits
            break;
        case 'n':
            move |= 3 << 12; // 3 shifted 12 bits
            break;
    }

    Chessboard::move(move);
}
