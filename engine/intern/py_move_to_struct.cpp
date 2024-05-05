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

    // handle promotion
    if ((mailbox[move.from] == WHITE_PAWN && move.to / 8 == 7)
        || (mailbox[move.from] == BLACK_PAWN && move.to / 8 == 0)) {

        move.promotion = true;

        if (isWhite(mailbox[move.from])) {
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
        }
        else {
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
        }
    }

    return move;
}
