#include "chessboard.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>


std::string Chessboard::getFen() {
    std::string fenString;

    std::string toStringBoard = toString();
    std::string fenStringBoard;

    std::istringstream f(toStringBoard);
    std::string line;    
    std::getline(f, line);
    std::string additionalFenInfo = line;
    for (int i = 0; i < 8; i++) {
        std::getline(f, line);
        fenStringBoard += line;
    }

    int emptySquares = 0;
    for (int i = 0; i < (int)fenStringBoard.length(); i++) {
        if (fenStringBoard[i] == '.') {
            emptySquares++;
        }
        else {
            if (emptySquares) {
                fenString += ('0' + emptySquares);
                emptySquares = 0;
            }
            fenString += fenStringBoard[i];
        }
        if ((i + 1) % 8 == 0) {
            if (emptySquares) {
                fenString += ('0' + emptySquares);
                emptySquares = 0;
            }
            fenString += "/";
        }
    }
    fenString.pop_back();
    fenString += " ";
    fenString += additionalFenInfo;

    return fenString;
}
