#include "chessboard.hpp"
#include "constants.hpp"
#include "board_info.hpp"
#include <tuple>
#include <vector>
#include <iostream>


BoardInfo Chessboard::getBoardInfoPy() {
    /*
    returns the current state of the board using the boardInfo class
    */

    BoardInfo info;

    // construct 2D board from mailbox
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            switch (board.mailbox[y * 8 + x]) {
                case WHITE_PAWN:
                    info.board[x][y] = 'P';
                    break;
                case WHITE_KNIGHT:
                    info.board[x][y] = 'N';
                    break;
                case WHITE_BISHOP:
                    info.board[x][y] = 'B';
                    break;
                case WHITE_ROOK:
                    info.board[x][y] = 'R';
                    break;
                case WHITE_QUEEN:
                    info.board[x][y] = 'Q';
                    break;
                case WHITE_KING:
                    info.board[x][y] = 'K';
                    break;
                case BLACK_PAWN:
                    info.board[x][y] = 'p';
                    break;
                case BLACK_KNIGHT:
                    info.board[x][y] = 'n';
                    break;
                case BLACK_BISHOP:
                    info.board[x][y] = 'b';
                    break;
                case BLACK_ROOK:
                    info.board[x][y] = 'r';
                    break;
                case BLACK_QUEEN:
                    info.board[x][y] = 'q';
                    break;
                case BLACK_KING:
                    info.board[x][y] = 'k';
                    break;
                default:
                    info.board[x][y] = ' ';
                    break;
            }
        }
    }

    info.turn = board.turn ? 'w': 'b';

    // convert en passant square
    info.enPassantSquare = std::make_tuple(-1, -1);
    if (board.enPassantSquare != 64) {
        info.enPassantSquare = std::make_tuple(board.enPassantSquare % 8, 
            board.enPassantSquare / 8);
    }

    return info;
}
