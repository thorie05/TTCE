#include "chessboard.hpp"
#include "constants.hpp"
#include "magic_data.hpp"
#include <iostream>
#include <tuple>


std::vector<U16> Chessboard::getPseudoLegalMoves() {
    /*
    returns all pseudo legal moves on the current position
    */

    std::vector<U16> pseudoLegalMoves;

    U64 friendlyPieces = turn ? bitboards[WHITE_PIECES]
        : bitboards[BLACK_PIECES];

    for (int sq = 0; sq < 64; sq++) {
        if (!(friendlyPieces & 1ULL << sq)) {
            continue;
        }

        int piece = mailbox[sq];
        U64 moveMask;

        switch (piece) {
            case WHITE_PAWN:
            case BLACK_PAWN:
                moveMask = getPawnMoveMask(sq);
                break;

            case WHITE_KNIGHT:
            case BLACK_KNIGHT:
                moveMask = KNIGHT_LOOKUP[sq];
                break;

            case WHITE_BISHOP:
            case BLACK_BISHOP:
                moveMask = getBishopMoveMask(sq);
                break;

            case WHITE_ROOK:
            case BLACK_ROOK:
                moveMask = getRookMoveMask(sq);
                break;

            case WHITE_QUEEN:
            case BLACK_QUEEN:
                moveMask = getBishopMoveMask(sq) | getRookMoveMask(sq);
                break;

            case WHITE_KING:
            case BLACK_KING:
                moveMask = KING_LOOKUP[sq];
                break;
        }

        moveMask &= ~friendlyPieces;

        for (int i = 0; i < 64; i++) {
            if (moveMask & 1ULL << i) {
                pseudoLegalMoves.push_back(sq | i << 6);
            }
        }
    }

    return pseudoLegalMoves;
}
