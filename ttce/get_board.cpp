#include "chessboard.hpp"

#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

std::tuple<std::vector<std::vector<std::string>>,std::string,std::tuple<bool,bool,bool,bool>,
    std::tuple<int,int>,int,int> Chessboard::getBoard() {
    // returns all properties of the chessboard like casling_rights or board position

    std::vector<std::vector<std::string>> twoDBoard(8, std::vector<std::string>(8, "."));

    // converts the board into a 8x8 2d vector of strings containing the pieces
    for (int i = 0; i < 64; i++) {
        if (bitboards.whitePawns & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'P';
        }
        if (bitboards.whiteKnights & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'N';
        }
        if (bitboards.whiteBishops & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'B';
        }
        if (bitboards.whiteRooks & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'R';
        }
        if (bitboards.whiteQueens & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'Q';
        }
        if (bitboards.whiteKing & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'K';
        }
        if (bitboards.blackPawns & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'p';
        }
        if (bitboards.blackKnights & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'n';
        }
        if (bitboards.blackBishops & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'b';
        }
        if (bitboards.blackRooks & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'r';
        }
        if (bitboards.blackQueens & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'q';
        }
        if (bitboards.blackKing & (1ULL << i)) {
            twoDBoard[i % 8][i / 8] = 'k';
        }
    }

    std::tuple<bool,bool,bool,bool> castlingRightsTuple = {castlingRights[0], castlingRights[1], 
        castlingRights[2], castlingRights[3]};

    std::tuple<int,int> enPassantSquareTuple = {enPassantSquare % 8, enPassantSquare / 8};
    if (enPassantSquare == -1) {
        enPassantSquareTuple = {-1, -1};
    }

    return {twoDBoard, turn, castlingRightsTuple, enPassantSquareTuple, halfmoveClock, fullMoveNumber};
}
