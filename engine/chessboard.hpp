#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "magic_data.hpp"
#include "board_info.hpp"
#include <string>
#include <stack>
#include <tuple>
#include <vector>
#include <iostream>
#include <array>
#include <unordered_map>

typedef unsigned long long U64;
typedef unsigned short U16;


class Chessboard {
    private:
        std::string inputFen;

        MagicData magic;

        std::array<int, 64> mailbox;
        std::array<U64, 16> bitboards;
        bool turn;

        // castling rights
        bool whiteCastleKingside;
        bool whiteCastleQueenside;
        bool blackCastleKingside;
        bool blackCastleQueenside;

        int enPassantSquare;
        int halfmoveClock;
        int turnNumber;

        // engine intern methods

        U16 pyMoveToU16(std::tuple<int,int>, std::tuple<int,int>, char);

        std::tuple<std::tuple<int,int>, std::tuple<int,int>, char>
            U16toPyMove(U16);

        std::vector<U16> getPseudoLegalMoves();

        std::vector<U16> getLegalMoves();

        bool isLegalMove(U16);

        void move(U16 move);

    public:
        Chessboard(const std::string& fen); // init

        // methods for the python module

        std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, 
            char>> getPseudoLegalMovesPy();

        std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, 
            char>> getLegalMovesPy();

        bool isLegalMovePy(std::tuple<int, int>, std::tuple<int, int>, char);

        void movePy(std::tuple<int,int>, std::tuple<int,int>, char);

        BoardInfo getBoardInfoPy();
};

#endif