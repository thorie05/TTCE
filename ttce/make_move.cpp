#include "chessboard.hpp"

#include <string>
#include <iostream>
#include <tuple>


void Chessboard::makeMove(int startSquare, int endSquare, const std::string& promotion = "") {
    // makes a move on the chessboard from start square to end square in bitboard square numbering

    std::cout << startSquare << " " << endSquare << std::endl;
    if (promotion.length() > 0) {
        std::cout << promotion << std::endl;
    }
}


void Chessboard::makeMove(const std::tuple<int,int>& startSquare, const std::tuple<int,int>& endSquare, 
    const std::string& promotion = "") {
    // makes a move on the chessboard from start square to end square given by the square coordinates

    // convert into bitboard square numbering and call makeMove
    int startSquareBitboard = 8 * std::get<1>(startSquare) + std::get<0>(startSquare);
    int endSquareBitboard = 8 * std::get<1>(endSquare) + std::get<0>(endSquare);
    makeMove(startSquareBitboard, endSquareBitboard, promotion);
}


void Chessboard::makeMove(const std::string& startSquare, const std::string& endSquare, 
    const std::string& promotion = "") {
    // makes a move on the chessboard from start square to end square given with algebraic notation

    // convert into bitboard square numbering and call makeMove
    int startSquareBitboard = algebraicToBitboardSquare(startSquare);
    int endSquareBitboard = algebraicToBitboardSquare(endSquare);
    makeMove(startSquareBitboard, endSquareBitboard, promotion);
}