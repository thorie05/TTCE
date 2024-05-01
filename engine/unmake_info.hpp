#ifndef UNMAKE_INFO_HPP
#define UNMAKE_INFO_HPP

typedef unsigned short U16;

struct UnmakeInfo {
    /*
    UnmakeInfo contains information necessary to recover the previous board and
    game state, like the last played move or the en passant square.
    */

    U16 move;
    int capturedPiece = EMPTY_SQUARE;
    bool promotion = false;
};

#endif

