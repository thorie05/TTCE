#include "chessboard.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::string Chessboard::toString() {
    // converts the chessboard into a readable string

    std::string out;

    // the first line is the same as the additional info of a fen string
    // turn
    out += turn + " "; 

    // castling rights
    if (castlingRights[0]) {
        out += "K";
    }
    if (castlingRights[1]) {
        out += "Q";
    }
    if (castlingRights[2]) {
        out += "k";
    }
    if (castlingRights[3]) {
        out += "q";
    }
    if (out.back() == ' ') {
        out += "-";
    }
    out += " ";

    // en passant square
    if (enPassantSquare == -1) {
        out += "- ";
    }
    else {
        out += bitboardToAlgebraicSquare(enPassantSquare) + " ";
    }

    // half move clock
    out += std::to_string(halfmoveClock) + " ";

    // number of full moves
    out += std::to_string(fullMoveNumber) + "\n";

    // convert the bitboards into a 8x8 vector of strings containing the pieces
    std::vector<std::string> stringBoard(8, "........");
    for (int i = 0; i < 64; i++) {
        if (bitboards.whitePawns & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'P';
        }
        if (bitboards.whiteKnights & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'N';
        }
        if (bitboards.whiteBishops & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'B';
        }
        if (bitboards.whiteRooks & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'R';
        }
        if (bitboards.whiteQueens & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'Q';
        }
        if (bitboards.whiteKing & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'K';
        }
        if (bitboards.blackPawns & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'p';
        }
        if (bitboards.blackKnights & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'n';
        }
        if (bitboards.blackBishops & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'b';
        }
        if (bitboards.blackRooks & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'r';
        }
        if (bitboards.blackQueens & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'q';
        }
        if (bitboards.blackKing & (1ULL << i)) {
            stringBoard[i / 8][i % 8] = 'k';
        }
    }
    std::reverse(stringBoard.begin(), stringBoard.end());

    for (int i = 0; i < 7; i++) {
        out += stringBoard[i] + "\n";
    }
    out += stringBoard[7];

    return out;
}
