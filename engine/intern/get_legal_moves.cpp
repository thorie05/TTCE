#include "chessboard.hpp"
#include "constants.hpp"
#include "magic_data.hpp"
#include <iostream>
#include <tuple>


void moveMaskToU16(int square, const U64& moveMask,
    std::vector<U16>& legalMoves) {
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
    /*
    returns all legal moves on the current position
    */

    std::vector<U16> legalMoves;

    if (turn) { // whites turn
        for (int sq = 0; sq < 64; sq++) {
            int piece = mailbox[sq];

            switch (piece) {
                case WHITE_PAWN: {
                    U64 moveMask = WHITE_PAWN_LOOKUP[sq];
                    U64 attackMask = WHITE_PAWN_ATTACK[sq];
                    U64 combinedMask = (moveMask & ~bitboards[PIECES])
                        | (attackMask & bitboards[BLACK_PIECES]);
                    // double pawn push
                    if (sq / 8 == 1 && (combinedMask & (1ULL << (sq + 8)))
                        && !(bitboards[PIECES] & (1ULL << (sq + 16)))) {
                        combinedMask |= 1ULL << (sq + 16);
                    }
                    moveMaskToU16(sq, combinedMask, legalMoves);
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

                case WHITE_KING: {
                    U64 moveMask = KING_LOOKUP[sq];
                    moveMask &= ~bitboards[WHITE_PIECES];
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
