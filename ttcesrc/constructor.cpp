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
                board.whitePawns |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'N': // white knight
                board.whiteKnights |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'B': // white bishop
                board.whiteBishops |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'R': // white rook
                board.whiteRooks |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'Q': // white queen
                board.whiteQueens |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'K': // white king
                board.whiteKing |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'p': // black pawn
                board.blackPawns |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'n': // black knight
                board.blackKnights |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'b': // black bishop
                board.blackBishops |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'r': // black rook
                board.blackRooks |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'q': // black queen
                board.blackQueens |= (1ULL << currentSquare);
                currentSquare++;
                break;

            case 'k': // black king
                board.blackKing |= (1ULL << currentSquare);
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

    board.whitePieces = board.whitePawns | board.whiteKnights 
        | board.whiteBishops | board.whiteRooks | board.whiteQueens 
        | board.whiteKing;

    board.blackPieces = board.blackPawns | board.blackKnights 
        | board.blackBishops | board.blackRooks | board.blackQueens 
        | board.blackKing;

    board.pieces = board.whitePieces | board.blackPieces;

    // whites turn is true, blacks turn is false
    board.turn = splitFen[1] == "w" ? true : false;

    // assign castling rights
    for (int i = 0; i < (int)splitFen[2].length(); i++) {
        if (splitFen[2][i] == 'K') {
            board.whiteCastleKingside = true;
        }
        if (splitFen[2][i] == 'Q') {
            board.whiteCastleQueenside = true;
        }
        if (splitFen[2][i] == 'k') {
            board.blackCastleKingside = true;
        }
        if (splitFen[2][i] == 'q') {
            board.blackCastleKingside = true;
        }
    }

    // en passant square
    if (splitFen[3] == "-") { // no en passant square
        board.enPassantSquare = 64;
    }
    else { // convert algebraic notation
        int file = splitFen[4][0] - 'a'; 
        int rank = splitFen[4][1] - '1';
        board.enPassantSquare = 8 * rank + file;
    }

    // initialize the half move clock
    board.halfmoveClock = stoi(splitFen[4]);

    // initialize the number of full moves
    board.turnNumber = stoi(splitFen[5]);
}