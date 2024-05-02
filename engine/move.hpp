#ifndef MOVE_HPP
#define MOVE_HPP

#include "constants.hpp"

struct Move {
    /*
    Contains information about a move.
    */

    int from;
    int to;
    bool promotion;
    int promotionPiece;

    // constructor
    Move() : from(0), to(0), promotion(false), promotionPiece(EMPTY_SQUARE) {}
    Move(int from, int to, bool promotion = false,
        int promotionPiece = EMPTY_SQUARE) : from(from), to(to),
        promotion(promotion), promotionPiece(promotionPiece) {}
};

#endif