#include "chessboard.hpp"
#include <tuple>
#include <vector>
#include <iostream>

std::tuple<std::vector<char>, char, bool, bool, bool, bool, int, int, int> Chessboard::getStatus() {
    std::vector board(64, ' ');

    for (int i = 0; i < 64; i++) {
        if (boardInfo.whitePawns & (1ULL << i)) {
            board[i] = 'P';
        }
        if (boardInfo.whiteKnights & (1ULL << i)) {
            board[i] = 'N';
        }
        if (boardInfo.whiteBishops & (1ULL << i)) {
            board[i] = 'B';
        }
        if (boardInfo.whiteRooks & (1ULL << i)) {
            board[i] = 'R';
        }
        if (boardInfo.whiteQueens & (1ULL << i)) {
            board[i] = 'Q';
        }
        if (boardInfo.whiteKing & (1ULL << i)) {
            board[i] = 'K';
        }
        if (boardInfo.blackPawns & (1ULL << i)) {
            board[i] = 'p';
        }
        if (boardInfo.blackKnights & (1ULL << i)) {
            board[i] = 'n';
        }
        if (boardInfo.blackBishops & (1ULL << i)) {
            board[i] = 'b';
        }
        if (boardInfo.blackRooks & (1ULL << i)) {
            board[i] = 'r';
        }
        if (boardInfo.blackQueens & (1ULL << i)) {
            board[i] = 'q';
        }
        if (boardInfo.blackKing & (1ULL << i)) {
            board[i] = 'k';
        }
    }

    char turn = boardInfo.turn ? 'w': 'b';

    return std::make_tuple(board, turn, boardInfo.whiteCastleKingside, boardInfo.whiteCastleQueenside, 
        boardInfo.blackCastleKingside, boardInfo.blackCastleQueenside, boardInfo.enPassantSquare,
        boardInfo.halfmoveClock, boardInfo.turnNumber);
}