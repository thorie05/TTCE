#ifndef UNMAKE_INFO_HPP
#define UNMAKE_INFO_HPP


struct UnmakeInfo {
    /*
    UnmakeInfo contains information necessary to recover the previous board and
    game state, like the last played move or the en passant square.
    */

    int from;
    int to;
    int capturedPiece = EMPTY_SQUARE;
    bool promotion = false;
    bool enPassant = false;
    bool whiteCastleKingside;
    bool whiteCastleQueenside;
    bool blackCastleKingside;
    bool blackCastleQueenside;
    int halfmoveClock = 0;
};

#endif

