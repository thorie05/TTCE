#include "chessboard.hpp"
#include <iostream>

Chessboard::Chessboard(const std::string& fenString): inputFen(fenString) {
    std::cout << inputFen << std::endl;
}