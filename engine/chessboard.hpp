#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "magic_data.hpp"
#include "unmake_info.hpp"
#include "board_info.hpp"
#include "move.hpp"
#include <string>
#include <stack>
#include <tuple>
#include <vector>
#include <iostream>
#include <array>
#include <unordered_map>
#include <stack>

typedef unsigned long long U64;


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

        Move pyMoveToStruct(const std::tuple<const int, const int>&,
            const std::tuple<const int, const int>&, char);

        std::tuple<std::tuple<int, int>, std::tuple<int, int>, char>
            structToPyMove(const Move);

        U64 getPawnMoveMask(const int);

        U64 getBishopMoveMask(const int);

        U64 getRookMoveMask(const int);

        std::vector<Move> getPseudoLegalMoves();

        std::vector<Move> getLegalMoves();

        bool isLegalMove(const Move);

        void move(const Move);

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