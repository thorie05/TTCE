#ifndef MOVE_HPP
#define MOVE_HPP

#include "constants.hpp"

struct Move {
    /*
    Contains information about a move.
    */

    int from;
    int to;
    bool enPassant = false;
    bool promotion = false;
    int promotionPiece = EMPTY_SQUARE;

    // constructor
    Move(int from, int to) : from(from), to(to) {}
};

#endif