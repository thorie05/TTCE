#include "chessboard.hpp"
#include "constants.hpp"
#include "magic_data.hpp"
#include "move.hpp"
#include <iostream>


std::vector<Move> Chessboard::getPseudoLegalMoves() {
    /*
    returns all pseudo legal moves on the current position
    */

    std::vector<Move> pseudoLegalMoves;

    U64 friendlyPieces = turn ? bitboards[WHITE_PIECES]
        : bitboards[BLACK_PIECES];

    for (int sq = 0; sq < 64; sq++) {
        if (!(friendlyPieces & 1ULL << sq)) {
            continue;
        }

        int piece = mailbox[sq];
        U64 moveMask;
        bool promotion = false;

        switch (piece) {
            case WHITE_PAWN:
            case BLACK_PAWN:
                moveMask = getPawnMoveMask(sq);

                // set promotion flag if pawn reaches back rank
                if ((piece == WHITE_PAWN && sq / 8 == 6)
                    || (piece == BLACK_PAWN && sq / 8 == 1)) {
                    promotion = true;
                }
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

        if (!promotion) {
            for (int i = 0; i < 64; i++) {
                if (moveMask & 1ULL << i) {
                    pseudoLegalMoves.push_back(Move(sq, i));
                }
            }
        }
        else {
            // include possible promotion pieces
            std::array<int, 4> promoPieces = turn ? WHITE_PROMO_PIECES
                : BLACK_PROMO_PIECES;

            for (int i = 0; i < 64; i++) {
                if (moveMask & 1ULL << i) {
                    for (int j = 0; j < (int)promoPieces.size(); j++) {
                        pseudoLegalMoves.push_back(Move(sq, i, true,
                            promoPieces[j]));
                    }
                }
            }
        }
    }

    return pseudoLegalMoves;
}
