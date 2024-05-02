#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "magic_data.hpp"
#include "unmake_info.hpp"
#include "board_info.hpp"
#include <string>
#include <stack>
#include <tuple>
#include <vector>
#include <iostream>
#include <array>
#include <unordered_map>
#include <stack>

typedef unsigned long long U64;
typedef unsigned short U16;


class Chessboard {
    /*
    The main class containing all functionality of the chess engine.
    */

    private:
        std::string inputFen;

        MagicData magic;

        std::stack<UnmakeInfo> unmakeStack;

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

        U16 pyMoveToU16(const std::tuple<int, int>&,
            const std::tuple<int, int>&, char);

        std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>
            U16toPyMove(const U16);

        U64 getPawnMoveMask(int);

        U64 getBishopMoveMask(int);

        U64 getRookMoveMask(int);

        std::vector<U16> getPseudoLegalMoves();

        std::vector<U16> getLegalMoves();

        bool isLegalMove(const U16);

        void move(const U16);

    public:
        Chessboard(const std::string&); // init

        void unmakeMove();

        // methods for the python module

        std::vector<std::tuple<std::tuple<int, int>,
            std::tuple<int, int>, char>> getPseudoLegalMovesPy();

        std::vector<std::tuple<std::tuple<int, int>,
            std::tuple<int, int>, char>> getLegalMovesPy();

        void movePy(const std::tuple<int, int>&, const std::tuple<int, int>&,
            char);

        BoardInfo getBoardInfoPy();
};

#endif