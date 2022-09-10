#include "chessboard.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>


std::string Chessboard::getFen() {
    // retunrns the fen string of the current board position

    std::string fenString;

    // get the string representation of the board
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

    // convert the 64 character string into the fen string
    int emptySquares = 0;
    for (int i = 0; i < (int)fenStringBoard.length(); i++) {
        if (fenStringBoard[i] == '.') { // . is an empty square
            emptySquares++;
        }
        // write the piece on the current position
        else {
            if (emptySquares) { // write the number of empty squares encountered until the piece
                fenString += ('0' + emptySquares);
                emptySquares = 0;
            }
            fenString += fenStringBoard[i]; 
        }
        // place a / if the end of the rank is reached
        if ((i + 1) % 8 == 0) { 
            if (emptySquares) { // write the number of empty squares encountered until the end of the row
                fenString += ('0' + emptySquares);
                emptySquares = 0;
            }
            fenString += "/";
        }
    }
    fenString.pop_back(); // remove the last /
    fenString += " ";
    fenString += additionalFenInfo; // add the additional info like castling rights

    return fenString;
}
