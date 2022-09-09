#include "chessboard.hpp"

#include <string>
#include <array>
#include <vector>
#include <utility>
#include <iostream>


Chessboard::Chessboard(const std::string& fenString = defaultFenString): inputFenString(fenString) {
    // initializes the board using the given fen string
    // if no string is passed the normal starting position is used

    // splits the fen string by whitespaces
    std::vector<std::string> splitFenString;
    std::string currentWord;
    for (int i = 0; i < (int)fenString.length(); i++) {
        if (fenString[i] == ' ' && currentWord.length()) {
            splitFenString.push_back(currentWord);
            currentWord = "";
        }
        else if (fenString[i] != ' ') {
            currentWord += fenString[i];
        }
    }
    if (currentWord.length()) {
        splitFenString.push_back(currentWord);
    }


    // initializes all bitboards
    int currentSquare = 56;
    for (int i = 0; i < (int)splitFenString[0].length(); i++) {
        char currentChar = splitFenString[0][i];

        switch (currentChar) {
            case 'P': // white pawn
                bitboards.whitePawns |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'N': // white knight
                bitboards.whiteKnights |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'B': // white bishop
                bitboards.whiteBishops |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'R': // white rook
                bitboards.whiteRooks |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'Q': // white queen
                bitboards.whiteQueens |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'K': // white king
                bitboards.whiteKing |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'p': // black pawn
                bitboards.blackPawns |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'n': // black knight
                bitboards.blackKnights |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'b': // black bishop
                bitboards.blackBishops |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'r': // black rook
                bitboards.blackRooks |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'q': // black queen
                bitboards.blackQueens |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'k': // black king
                bitboards.blackKing |= (1ULL << currentSquare);
                currentSquare++;
                break;
            
            case '/': // new rank
                currentSquare -= 16;
                break;

            default: // digit or invalid character
                if (isdigit(currentChar)) {
                    currentSquare += currentChar - '0';
                }
                // if invalid character nothing happens
                break;
        }
    }
    bitboards.whitePieces = bitboards.whitePawns | bitboards.whiteKnights | bitboards.whiteBishops | 
        bitboards.whiteRooks | bitboards.whiteQueens | bitboards.whiteKing;
    bitboards.blackPieces = bitboards.blackPawns | bitboards.blackKnights | bitboards.blackBishops | 
        bitboards.blackRooks | bitboards.blackQueens | bitboards.blackKing;
    bitboards.pieces = bitboards.whitePieces | bitboards.blackPieces;

    // initializes the turn
    turn = splitFenString[1];

    // initializes the castling rights
    if (splitFenString[2] != "-") {
        for (int i = 0; i < (int)splitFenString[2].length(); i++) {
            switch (splitFenString[2][i]) {
                case 'K':
                    castlingRights[0] = true;
                    break;
                case 'Q':
                    castlingRights[1] = true;
                    break;
                case 'k':
                    castlingRights[2] = true;
                    break;
                case 'q':
                    castlingRights[3] = true;
                    break;
            }
        }
    }

    // initializes the en passant square
    if (splitFenString[3] != "-") {
        enPassantSquare = algebraicToBitboardSquare(splitFenString[3]);
    }

    // initializes the half move clock
    halfmoveClock = stoi(splitFenString[4]);

    // initializes the number of full moves
    fullMoveNumber = stoi(splitFenString[5]);
}
