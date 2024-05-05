#include "chessboard.hpp"
#include "constants.hpp"
#include "magic_data.hpp"
#include "move.hpp"
#include <iostream>
#include <array>


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
                moveMask = getWhitePawnMoveMask(sq);
                if (sq / 8 == 6) {
                    promotion = true;
                }
                break;

            case BLACK_PAWN:
                if (sq / 8 == 1) {
                    promotion = true;
                }
                moveMask = getBlackPawnMoveMask(sq);
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

        if (promotion) {
            // include promotion to every possible piece if promoting
            std::array<int, 4> promoPieces = turn ? WHITE_PROMO_PIECES
                : BLACK_PROMO_PIECES;
            for (int i = 0; i < 64; i++) {
                if (moveMask & 1ULL << i) {
                    for (int j = 0; j < (int)promoPieces.size(); j++) {
                        Move move(sq, i);
                        move.promotion = true;
                        move.promotionPiece = promoPieces[j];
                        pseudoLegalMoves.push_back(move);
                    }
                }
            }
        }
        else {
            for (int i = 0; i < 64; i++) {
                if (moveMask & 1ULL << i) {
                    pseudoLegalMoves.push_back(Move(sq, i));
                }
            }
        }
    }

    if (turn) {
        // add castling moves for white
        if (whiteCastleKingside && !(bitboards[PIECES] & 0x60)) {
            pseudoLegalMoves.push_back(Move(4, 6));
        }
        if (whiteCastleQueenside && !(bitboards[PIECES] & 0xe)) {
            pseudoLegalMoves.push_back(Move(4, 2));
        }
    }
    else {
        // add castling moves for black
        if (blackCastleKingside && !(bitboards[PIECES] & 0x6000000000000000)) {
            pseudoLegalMoves.push_back(Move(60, 62));
        }
        if (blackCastleQueenside && !(bitboards[PIECES] & 0xe00000000000000)) {
            pseudoLegalMoves.push_back(Move(60, 58));
        }
    }

    return pseudoLegalMoves;
}
