#include "chessboard.hpp"
#include "constants.hpp"
#include "position.hpp"
#include "magic_data.hpp"
#include <iostream>
#include <tuple>


void moveMaskToU16(int square, U64 moveMask, std::vector<U16>& legalMoves) {
    /*
    convert move mask bitboard to U16 format
    */

    for (int i = 0; i < 64; i++) {
        if (moveMask & 1ULL << i) {
            legalMoves.push_back(square | i << 6);
        }
    }
}


U64 getBishopMask(int square, const Position& board, const MagicData& magic) {
    /*
    returns move mask for the bishop on the given square
    */

    // calculate lookup key
    U64 key = board.bitboards[PIECES] & magic.bishopMasks[square];
    key *= magic.bishopMagicNumbers[square];
    key >>= magic.bishopShifts[square];
    key += magic.bishopLookupIndex[square];

    // get moves using that key
    U64 moveMask = magic.bishopLookup[key];

    // remove friendly pieces
    moveMask &= ~board.bitboards[WHITE_PIECES];

    return moveMask;
}


U64 getRookMask(int square, const Position& board, const MagicData& magic) {
    /*
    returns move mask for the rook on the given square
    */

    // calculate lookup key
    U64 key = board.bitboards[PIECES] & magic.rookMasks[square];
    key *= magic.rookMagicNumbers[square];
    key >>= magic.rookShifts[square];
    key += magic.rookLookupIndex[square];

    // get moves using that key
    U64 moveMask = magic.rookLookup[key];

    // remove friendly pieces
    moveMask &= ~board.bitboards[WHITE_PIECES];

    return moveMask;
}


U64 getQueenMask(int square, const Position& board, const MagicData& magic) {
    /*
    returns move mask for the rook on the given square
    */

    return getBishopMask(square, board, magic)
        | getRookMask(square, board, magic);
}


std::vector<U16> Chessboard::getLegalMoves() {
    std::vector<U16> legalMoves;
    /*
    returns all legal moves on the current position
    */

    if (board.turn) { // whites turn
        for (int sq = 0; sq < 64; sq++) {
            int piece = board.mailbox[sq];

            switch (piece) {
                case WHITE_PAWN: {
                    break;
                }

                case WHITE_BISHOP: {
                    U64 moveMask = getBishopMask(sq, board, magic);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_ROOK: {
                    U64 moveMask = getRookMask(sq, board, magic);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_QUEEN: {
                    U64 moveMask = getQueenMask(sq, board, magic);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }
            }
        }
    }
    else { // blacks turn

    }

    return legalMoves;
}
