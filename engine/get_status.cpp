#include "chessboard.hpp"
#include <tuple>
#include <vector>
#include <iostream>

std::tuple<std::vector<std::vector<char>>, char, bool, bool, bool, bool, 
    std::tuple<int,int>, int, int> Chessboard::getStatus() {
    // returns the current state of the board

    std::vector<std::vector<char>> returnBoard(8, std::vector<char>(8, ' '));
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            switch (board.mailbox[y * 8 + x]) {
                case WHITE_PAWN:
                    returnBoard[x][y] = 'P';
                    break;
                case WHITE_KNIGHT:
                    returnBoard[x][y] = 'N';
                    break;
                case WHITE_BISHOP:
                    returnBoard[x][y] = 'B';
                    break;
                case WHITE_ROOK:
                    returnBoard[x][y] = 'R';
                    break;
                case WHITE_QUEEN:
                    returnBoard[x][y] = 'Q';
                    break;
                case WHITE_KING:
                    returnBoard[x][y] = 'K';
                    break;
                case BLACK_PAWN:
                    returnBoard[x][y] = 'p';
                    break;
                case BLACK_KNIGHT:
                    returnBoard[x][y] = 'n';
                    break;
                case BLACK_BISHOP:
                    returnBoard[x][y] = 'b';
                    break;
                case BLACK_ROOK:
                    returnBoard[x][y] = 'r';
                    break;
                case BLACK_QUEEN:
                    returnBoard[x][y] = 'q';
                    break;
                case BLACK_KING:
                    returnBoard[x][y] = 'k';
                    break;
            }
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