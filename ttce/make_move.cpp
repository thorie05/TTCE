#include "chessboard.hpp"

#include <string>
#include <iostream>
#include <tuple>
#include <vector>


void Chessboard::makeMove(int startSquare, int endSquare, const std::string& promotion = "", bool changeTurn = true) {
    // makes a move on the chessboard from start square to end square in bitboard square numbering

    // clear the end square
    bitboards.whitePawns &= ~(1ULL << endSquare);
    bitboards.whiteKnights &= ~(1ULL << endSquare);
    bitboards.whiteBishops &= ~(1ULL << endSquare);
    bitboards.whiteRooks &= ~(1ULL << endSquare);
    bitboards.whiteQueens &= ~(1ULL << endSquare);
    bitboards.whiteKing &= ~(1ULL << endSquare);
    bitboards.whitePieces &= ~(1ULL << endSquare);
    bitboards.blackPawns &= ~(1ULL << endSquare);
    bitboards.blackKnights &= ~(1ULL << endSquare);
    bitboards.blackBishops &= ~(1ULL << endSquare);
    bitboards.blackRooks &= ~(1ULL << endSquare);
    bitboards.blackQueens &= ~(1ULL << endSquare);
    bitboards.blackKing &= ~(1ULL << endSquare);
    bitboards.blackPieces &= ~(1ULL << endSquare);

    // move the piece from the start square to the end square
    if (bitboards.whitePawns & (1ULL << startSquare)) {
        bitboards.whitePawns &= ~(1ULL << startSquare);
        bitboards.whitePawns |= (1ULL << endSquare);

        bitboards.whitePieces &= ~(1ULL << startSquare);
        bitboards.whitePieces |= (1ULL << endSquare);
    }
    else if (bitboards.blackPawns & (1ULL << startSquare)) {
        bitboards.blackPawns &= ~(1ULL << startSquare);
        bitboards.blackPawns |= (1ULL << endSquare);

        bitboards.blackPieces &= ~(1ULL << startSquare);
        bitboards.blackPieces |= (1ULL << endSquare);
    }
    else if (bitboards.whiteKnights & (1ULL << startSquare)) {
        bitboards.whiteKnights &= ~(1ULL << startSquare);
        bitboards.whiteKnights |= (1ULL << endSquare);

        bitboards.whitePieces &= ~(1ULL << startSquare);
        bitboards.whitePieces |= (1ULL << endSquare);
    }
    else if (bitboards.blackKnights & (1ULL << startSquare)) {
        bitboards.blackKnights &= ~(1ULL << startSquare);
        bitboards.blackKnights |= (1ULL << endSquare);

        bitboards.blackPieces &= ~(1ULL << startSquare);
        bitboards.blackPieces |= (1ULL << endSquare);
    }
    else if (bitboards.whiteBishops & (1ULL << startSquare)) {
        bitboards.whiteBishops &= ~(1ULL << startSquare);
        bitboards.whiteBishops |= (1ULL << endSquare);

        bitboards.whitePieces &= ~(1ULL << startSquare);
        bitboards.whitePieces |= (1ULL << endSquare);
    }
    else if (bitboards.blackBishops & (1ULL << startSquare)) {
        bitboards.blackBishops &= ~(1ULL << startSquare);
        bitboards.blackBishops |= (1ULL << endSquare);

        bitboards.blackPieces &= ~(1ULL << startSquare);
        bitboards.blackPieces |= (1ULL << endSquare);
    }
    else if (bitboards.whiteRooks & (1ULL << startSquare)) {
        bitboards.whiteRooks &= ~(1ULL << startSquare);
        bitboards.whiteRooks |= (1ULL << endSquare);

        bitboards.whitePieces &= ~(1ULL << startSquare);
        bitboards.whitePieces |= (1ULL << endSquare);
    }
    else if (bitboards.blackRooks & (1ULL << startSquare)) {
        bitboards.blackRooks &= ~(1ULL << startSquare);
        bitboards.blackRooks |= (1ULL << endSquare);

        bitboards.blackPieces &= ~(1ULL << startSquare);
        bitboards.blackPieces |= (1ULL << endSquare);
    }
    else if (bitboards.whiteQueens & (1ULL << startSquare)) {
        bitboards.whiteQueens &= ~(1ULL << startSquare);
        bitboards.whiteQueens |= (1ULL << endSquare);

        bitboards.whitePieces &= ~(1ULL << startSquare);
        bitboards.whitePieces |= (1ULL << endSquare);
    }
    else if (bitboards.blackQueens & (1ULL << startSquare)) {
        bitboards.blackQueens &= ~(1ULL << startSquare);
        bitboards.blackQueens |= (1ULL << endSquare);

        bitboards.blackPieces &= ~(1ULL << startSquare);
        bitboards.blackPieces |= (1ULL << endSquare);
    }
    else if (bitboards.whiteKing & (1ULL << startSquare)) {
        bitboards.whiteKing &= ~(1ULL << startSquare);
        bitboards.whiteKing |= (1ULL << endSquare);

        bitboards.whitePieces &= ~(1ULL << startSquare);
        bitboards.whitePieces |= (1ULL << endSquare);
    }
    else if (bitboards.blackKing & (1ULL << startSquare)) {
        bitboards.blackKing &= ~(1ULL << startSquare);
        bitboards.blackKing |= (1ULL << endSquare);

        bitboards.blackPieces &= ~(1ULL << startSquare);
        bitboards.blackPieces |= (1ULL << endSquare);
    }

    if (changeTurn) {
        // change turn from w to b and from b to w
        turn = turn == "w" ? "b" : "w";
    }
}


void Chessboard::makeMove(const std::tuple<int,int>& startSquare, const std::tuple<int,int>& endSquare, 
    const std::string& promotion = "", bool changeTurn = true) {
    // makes a move on the chessboard from start square to end square given by the square coordinates

    // convert into bitboard square numbering and call makeMove
    int startSquareBitboard = 8 * std::get<1>(startSquare) + std::get<0>(startSquare);
    int endSquareBitboard = 8 * std::get<1>(endSquare) + std::get<0>(endSquare);
    makeMove(startSquareBitboard, endSquareBitboard, promotion, changeTurn);
}


void Chessboard::makeMove(const std::string& startSquare, const std::string& endSquare, 
    const std::string& promotion = "", bool changeTurn = true) {
    // makes a move on the chessboard from start square to end square given with algebraic notation

    // convert into bitboard square numbering and call makeMove
    int startSquareBitboard = algebraicToBitboardSquare(startSquare);
    int endSquareBitboard = algebraicToBitboardSquare(endSquare);
    makeMove(startSquareBitboard, endSquareBitboard, promotion, changeTurn);
}
