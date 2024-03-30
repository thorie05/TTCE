#include "chessboard.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <array>

Chessboard::Chessboard(const std::string& fen): inputFen(fen) {
    // initializes the board using the given fen string

    // split fen by spaces
    std::string s;
    std::stringstream ss(fen);
    std::array<std::string,6> splitFen;
    for (int i = 0; i < 6; i++) {
        std::getline(ss, s, ' ');
        splitFen[i] = s;
    }

    // fill bitboards
    int currentSquare = 56;
    for (int i = 0; i < (int)splitFen[0].length(); i++) {
        char currentChar = splitFen[0][i];
        switch (currentChar) {
            case 'P': // white pawn
                boardInfo.whitePawns |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'N': // white knight
                boardInfo.whiteKnights |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'B': // white bishop
                boardInfo.whiteBishops |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'R': // white rook
                boardInfo.whiteRooks |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'Q': // white queen
                boardInfo.whiteQueens |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'K': // white king
                boardInfo.whiteKing |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'p': // black pawn
                boardInfo.blackPawns |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'n': // black knight
                boardInfo.blackKnights |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'b': // black bishop
                boardInfo.blackBishops |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'r': // black rook
                boardInfo.blackRooks |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'q': // black queen
                boardInfo.blackQueens |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'k': // black king
                boardInfo.blackKing |= (1ULL << currentSquare);
                currentSquare++;
                break;
            
            case '/': // new rank
                currentSquare -= 16;
                break;

            default: // digit
                if (isdigit(currentChar)) {
                    currentSquare += currentChar - '0';
                }
                break;
        }
    }

    boardInfo.whitePieces = boardInfo.whitePawns | boardInfo.whiteKnights | boardInfo.whiteBishops | 
        boardInfo.whiteRooks | boardInfo.whiteQueens | boardInfo.whiteKing;

    boardInfo.blackPieces = boardInfo.blackPawns | boardInfo.blackKnights | boardInfo.blackBishops | 
        boardInfo.blackRooks | boardInfo.blackQueens | boardInfo.blackKing;

    boardInfo.pieces = boardInfo.whitePieces | boardInfo.blackPieces;

    // whites turn is true, blacks turn is false
    boardInfo.turn = splitFen[1] == "w" ? true : false;

    // assign castling rights
    for (int i = 0; i < (int)splitFen[2].length(); i++) {
        if (splitFen[2][i] == 'K') {
            boardInfo.whiteCastleKingside = true;
        }
        if (splitFen[2][i] == 'Q') {
            boardInfo.whiteCastleQueenside = true;
        }
        if (splitFen[2][i] == 'k') {
            boardInfo.blackCastleKingside = true;
        }
        if (splitFen[2][i] == 'q') {
            boardInfo.blackCastleKingside = true;
        }
    }

    // en passant square
    if (splitFen[3] == "-") { // no en passant square
        boardInfo.enPassantSquare = 64;
    }
    else { // convert algebraic notation
        int file = splitFen[4][0] - 'a'; 
        int rank = splitFen[4][1] - '1';
        boardInfo.enPassantSquare = 8 * rank + file;
    }

    // initialize the half move clock
    boardInfo.halfmoveClock = stoi(splitFen[4]);

    // initialize the number of full moves
    boardInfo.turnNumber = stoi(splitFen[5]);
}