#include "chessboard.hpp"
#include "constants.hpp"
#include "move.hpp"
#include <tuple>


Move Chessboard::pyMoveToStruct(const std::tuple<const int, const int>& from,
    const std::tuple<const int, const int>& to, char promotionPiece = 'q') {
    /*
    translates python move to Move struct
    */

    Move move(std::get<1>(from) * 8 + std::get<0>(from),
        std::get<1>(to) * 8 + std::get<0>(to));

    // handle promotion and en passant
    if (mailbox[move.from] == WHITE_PAWN) {
        if (move.to / 8 == 7) {
            // set promotion piece for white
            switch (promotionPiece) {
                case 'n':
                    move.promotionPiece = WHITE_KNIGHT;
                    break;
                case 'b':
                    move.promotionPiece = WHITE_BISHOP;
                    break;
                case 'r':
                    move.promotionPiece = WHITE_ROOK;
                    break;
                case 'q':
                    move.promotionPiece = WHITE_QUEEN;
                    break;
            }
            move.promotion = true;

        }
        // set en passant flag if en passant 
        else if (move.from != enPassantSquare && move.to == enPassantSquare + 8
            && mailbox[enPassantSquare + 8] == EMPTY_SQUARE) {
            move.enPassant = true;
        }
    }
    else if (mailbox[move.from] == BLACK_PAWN) {
        if (move.to / 8 == 0) {
            // set promotion piece for black
            switch (promotionPiece) {
                case 'n':
                    move.promotionPiece = BLACK_KNIGHT;
                    break;
                case 'b':
                    move.promotionPiece = BLACK_BISHOP;
                    break;
                case 'r':
                    move.promotionPiece = BLACK_ROOK;
                    break;
                case 'q':
                    move.promotionPiece = BLACK_QUEEN;
                    break;
            }
            move.promotion = true;
        }
        // set en passant flag if en passant 
        else if (move.from != enPassantSquare && move.to == enPassantSquare - 8
            && mailbox[enPassantSquare - 8] == EMPTY_SQUARE) {
            move.enPassant = true;
        }
    }

    return move;
}
