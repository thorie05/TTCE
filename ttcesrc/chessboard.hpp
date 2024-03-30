#include <string>
#include <stack>
#include <tuple>
#include <vector>

typedef unsigned long long U64;
typedef unsigned short U16;

const std::string defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

struct Board {
    // bitboards
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
        std::tuple<std::vector<char>, char, bool, bool, bool, bool, int, int, int> getStatus();
};
