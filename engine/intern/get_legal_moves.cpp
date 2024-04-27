#include "chessboard.hpp"
#include "constants.hpp"
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


U64 getBishopMask(int square, const std::array<U64, 16>& bitboards,
    const MagicData& magic) {
    /*
    returns move mask for the bishop on the given square
    */

    // calculate lookup key
    U64 key = bitboards[PIECES] & magic.bishopMasks[square];
    key *= magic.bishopMagicNumbers[square];
    key >>= magic.bishopShifts[square];
    key += magic.bishopLookupIndex[square];

    // get moves using that key
    U64 moveMask = magic.bishopLookup[key];

    // remove friendly pieces
    moveMask &= ~bitboards[WHITE_PIECES];

    return moveMask;
}


U64 getRookMask(int square, const std::array<U64, 16>& bitboards,
    const MagicData& magic) {
    /*
    returns move mask for the rook on the given square
    */

    // calculate lookup key
    U64 key = bitboards[PIECES] & magic.rookMasks[square];
    key *= magic.rookMagicNumbers[square];
    key >>= magic.rookShifts[square];
    key += magic.rookLookupIndex[square];

    // get moves using that key
    U64 moveMask = magic.rookLookup[key];

    // remove friendly pieces
    moveMask &= ~bitboards[WHITE_PIECES];

    return moveMask;
}


std::vector<U16> Chessboard::getLegalMoves() {
    std::vector<U16> legalMoves;
    /*
    returns all legal moves on the current position
    */

    if (turn) { // whites turn
        for (int sq = 0; sq < 64; sq++) {
            int piece = mailbox[sq];

            switch (piece) {
                case WHITE_PAWN: {
                    break;
                }

                case WHITE_KNIGHT: {
                    U64 moveMask = KNIGHT_LOOKUP[sq];
                    moveMask &= ~bitboards[WHITE_PIECES];
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_BISHOP: {
                    U64 moveMask = getBishopMask(sq, bitboards, magic);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_ROOK: {
                    U64 moveMask = getRookMask(sq, bitboards, magic);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_QUEEN: {
                    U64 moveMask = getBishopMask(sq, bitboards, magic)
                        | getRookMask(sq, bitboards, magic);
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
