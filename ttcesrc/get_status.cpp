#include "chessboard.hpp"
#include <tuple>
#include <vector>
#include <iostream>

std::tuple<std::vector<char>, char, bool, bool, bool, bool, int, int, int> 
    Chessboard::getStatus() {
    // returns the current state of the board

    std::vector returnBoard(64, ' ');
    for (int i = 0; i < 64; i++) {
        if (board.whitePawns & (1ULL << i)) {
            returnBoard[i] = 'P'; // white pawn
        }
        if (board.whiteKnights & (1ULL << i)) {
            returnBoard[i] = 'N'; // white knight
        }
        if (board.whiteBishops & (1ULL << i)) {
            returnBoard[i] = 'B'; // white bishop
        }
        if (board.whiteRooks & (1ULL << i)) {
            returnBoard[i] = 'R'; // white rook
        }
        if (board.whiteQueens & (1ULL << i)) {
            returnBoard[i] = 'Q'; // white queen
        }
        if (board.whiteKing & (1ULL << i)) {
            returnBoard[i] = 'K'; // white king
        }
        if (board.blackPawns & (1ULL << i)) {
            returnBoard[i] = 'p'; // black pawn
        }
        if (board.blackKnights & (1ULL << i)) {
            returnBoard[i] = 'n'; // black knight
        }
        if (board.blackBishops & (1ULL << i)) {
            returnBoard[i] = 'b'; // black bishop
        }
        if (board.blackRooks & (1ULL << i)) {
            returnBoard[i] = 'r'; // black rook
        }
        if (board.blackQueens & (1ULL << i)) {
            returnBoard[i] = 'q'; // black queen
        }
        if (board.blackKing & (1ULL << i)) {
            returnBoard[i] = 'k'; // black king
        }
    }

    char returnTurn = board.turn ? 'w': 'b';

    return std::make_tuple(returnBoard, returnTurn, board.whiteCastleKingside, 
        board.whiteCastleQueenside, board.blackCastleKingside, 
        board.blackCastleQueenside, board.enPassantSquare, board.halfmoveClock, 
        board.turnNumber);
}