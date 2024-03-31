#include "chessboard.hpp"
#include <tuple>
#include <vector>
#include <iostream>

std::tuple<std::vector<std::vector<char>>, char, bool, bool, bool, bool, 
    std::tuple<int,int>, int, int> Chessboard::getStatus() {
    // returns the current state of the board

    std::vector<std::vector<char>> returnBoard(8, std::vector<char>(8, ' '));
    int i = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board.whitePawns & (1ULL << i)) {
                returnBoard[x][y] = 'P'; // white pawn
            }
            if (board.whiteKnights & (1ULL << i)) {
                returnBoard[x][y] = 'N'; // white knight
            }
            if (board.whiteBishops & (1ULL << i)) {
                returnBoard[x][y] = 'B'; // white bishop
            }
            if (board.whiteRooks & (1ULL << i)) {
                returnBoard[x][y] = 'R'; // white rook
            }
            if (board.whiteQueens & (1ULL << i)) {
                returnBoard[x][y] = 'Q'; // white queen
            }
            if (board.whiteKing & (1ULL << i)) {
                returnBoard[x][y] = 'K'; // white king
            }
            if (board.blackPawns & (1ULL << i)) {
                returnBoard[x][y] = 'p'; // black pawn
            }
            if (board.blackKnights & (1ULL << i)) {
                returnBoard[x][y] = 'n'; // black knight
            }
            if (board.blackBishops & (1ULL << i)) {
                returnBoard[x][y] = 'b'; // black bishop
            }
            if (board.blackRooks & (1ULL << i)) {
                returnBoard[x][y] = 'r'; // black rook
            }
            if (board.blackQueens & (1ULL << i)) {
                returnBoard[x][y] = 'q'; // black queen
            }
            if (board.blackKing & (1ULL << i)) {
                returnBoard[x][y] = 'k'; // black king
            }

            i++;
        }
    }

    char returnTurn = board.turn ? 'w': 'b';

    // convert en passant square
    std::tuple<int,int> returnEnPassantSquare = std::make_tuple(-1, -1);
    if (board.enPassantSquare != 64) {
        returnEnPassantSquare = std::make_tuple(board.enPassantSquare % 8, 
            board.enPassantSquare / 8);
    }

    return std::make_tuple(returnBoard, returnTurn, board.whiteCastleKingside, 
        board.whiteCastleQueenside, board.blackCastleKingside, 
        board.blackCastleQueenside, returnEnPassantSquare, board.halfmoveClock, 
        board.turnNumber);
}