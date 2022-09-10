#include <string>
#include <array>
#include <utility>
#include <tuple>
#include <vector>
#include <stack>

#define U64 unsigned long long


inline std::string defaultFenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";


struct Board {
    // Board struct containing all necessary bitboards

   U64 whitePawns = 0;
   U64 whiteKnights = 0;
   U64 whiteBishops = 0;
   U64 whiteRooks = 0;
   U64 whiteQueens = 0;
   U64 whiteKing = 0;

   U64 blackPawns = 0;
   U64 blackKnights = 0;
   U64 blackBishops = 0;
   U64 blackRooks = 0;
   U64 blackQueens = 0;
   U64 blackKing = 0;

   U64 whitePieces = 0;
   U64 blackPieces = 0;
   U64 pieces = 0;
};


struct HistoryBoard {
    Board bitboards;
    std::string turn;
    std::array<bool,4> castlingRights;
    int enPassantSquare;
    int halfmoveClock;
    int fullMoveNumber;
};


class Chessboard {
 
    private:

        std::string inputFenString;
        Board bitboards;
        std::string turn;
        std::array<bool,4> castlingRights = {false, false, false, false};
        int enPassantSquare = -1;
        int halfmoveClock;
        int fullMoveNumber;
        std::stack<HistoryBoard> history;

    public:

        Chessboard(const std::string& fenString);

        std::tuple<std::vector<std::vector<std::string>>,std::string,
            std::tuple<bool,bool,bool,bool>,std::tuple<int,int>,int,int> getBoard();

        std::string getFen();

        std::string toString();

        void makeMove(int, int, const std::string&, bool);
        void makeMove(const std::tuple<int,int>&, const std::tuple<int,int>&, const std::string&, bool);
        void makeMove(const std::string&, const std::string&, const std::string&, bool);

        void unmakeLastMove();
};


int algebraicToBitboardSquare(std::string);
std::string bitboardToAlgebraicSquare(int);
