#include <string>
#include <stack>
#include <tuple>
#include <vector>
#include <iostream>
#include <array>

typedef unsigned long long U64;
typedef unsigned short U16;

const std::string DEFAULT_FEN = 
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

// constants for encoding pieces in bitboards and mailbox array
const int WHITE_PAWN = 0;
const int WHITE_KNIGHT = 1;
const int WHITE_BISHOP = 2;
const int WHITE_ROOK = 3;
const int WHITE_QUEEN = 4;
const int WHITE_KING = 5;
const int BLACK_PAWN = 6;
const int BLACK_KNIGHT = 7;
const int BLACK_BISHOP = 8;
const int BLACK_ROOK = 9;
const int BLACK_QUEEN = 10;
const int BLACK_KING = 11;

const int WHITE_PIECES = 12;
const int BLACK_PIECES = 13;
const int PIECES = 14;

const int EMPTY_SQUARE = 15;

struct Board {
    // struct representing board position

    std::array<U16, 64> mailbox;
    std::array<U64, 16> bitboards{}; // index 15 redundant

    bool turn;

    // castling rights
    bool whiteCastleKingside;
    bool whiteCastleQueenside;
    bool blackCastleKingside;
    bool blackCastleQueenside;

    U16 enPassantSquare;
    U16 halfmoveClock;
    U16 turnNumber;
};

class Chessboard {
    private:
        std::string inputFen;
        Board board;
        std::stack<Board> history;

    public:
        Chessboard(const std::string& fen);

        std::tuple<std::vector<std::vector<char>>, char, bool, bool, bool, bool,
            std::tuple<int,int>, int, int> getStatus();

        void pushMove(U16 move);

        void pushMove(std::tuple<int,int> startSquare, 
            std::tuple<int,int> endSquare, char promotion);

        std::vector<U16> getPseudoLegalMoves();

        std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, 
            char>> getPseudoLegalMovesPy();
};
