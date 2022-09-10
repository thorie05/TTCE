#include "chessboard.hpp"


void Chessboard::unmakeLastMove() {
    // umakes the last move

    if (history.empty()) {
        return;
    }

    HistoryBoard lastState = history.top();
    history.pop();

    bitboards = lastState.bitboards;
    turn = lastState.turn;
    castlingRights = lastState.castlingRights;
    enPassantSquare = lastState.enPassantSquare;
    halfmoveClock = lastState.halfmoveClock;
    fullMoveNumber = lastState.fullMoveNumber;
}
