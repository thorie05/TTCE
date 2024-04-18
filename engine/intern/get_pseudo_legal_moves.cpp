#include "chessboard.hpp"
#include "constants.hpp"
#include <iostream>
#include <tuple>

std::vector<U16> Chessboard::getPseudoLegalMoves() {
    std::vector<U16> pseudoLegalMoves;
    // returns all pseudo legal moves

    if (board.turn) { // whites turn
        for (int i = 0; i < 64; i++) {
            int piece = board.mailbox[i];

            switch (piece) {
                case WHITE_PAWN: {
                    if (!(board.bitboards[PIECES] & 1ULL<<(i + 8))) {
                        // move one square forward
                        pseudoLegalMoves.push_back(i | (i + 8) << 6);
                        if (!(board.bitboards[PIECES] & 1ULL<<(i + 16)) 
                            && i >= 8 && i <= 15) {
                            // move two squares forward
                            pseudoLegalMoves.push_back(i | (i + 16) << 6);
                        }
                    }
                    break;
                }

                case WHITE_BISHOP: {
                    U64 bkey = board.bitboards[PIECES] & magic.bishopMasks[i];
                    bkey *= magic.bishopMagicNumbers[i];
                    bkey >>= magic.bishopShifts[i];
                    bkey += magic.bishopLookupIndex[i];
                    U64 bishopMoveMask = magic.bishopLookup[bkey];
                    bishopMoveMask &= ~board.bitboards[WHITE_PIECES];
                    for (int j = 0; j < 64; j++) {
                        if (bishopMoveMask & 1ULL << j) {
                            pseudoLegalMoves.push_back(i | j << 6);
                        }
                    }
                    break;
                }

                case WHITE_ROOK: {
                    U64 rkey = board.bitboards[PIECES] & magic.rookMasks[i];
                    rkey *= magic.rookMagicNumbers[i];
                    rkey >>= magic.rookShifts[i];
                    rkey += magic.rookLookupIndex[i];
                    U64 rookMoveMask = magic.rookLookup[rkey];
                    rookMoveMask &= ~board.bitboards[WHITE_PIECES];
                    for (int j = 0; j < 64; j++) {
                        if (rookMoveMask & 1ULL << j) {
                            pseudoLegalMoves.push_back(i | j << 6);
                        }
                    }
                    break;
                }
            }
        }
    }
    else { // blacks turn

    }

    return pseudoLegalMoves;
}
