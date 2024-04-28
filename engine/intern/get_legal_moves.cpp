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
    const MagicData& magic, const U64& friendly) {
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
    moveMask &= ~bitboards[friendly];

    return moveMask;
}


U64 getRookMask(int square, const std::array<U64, 16>& bitboards,
    const MagicData& magic, int friendly) {
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
    moveMask &= ~bitboards[friendly];

    return moveMask;
}


void getWhitePawnMoves(int square, const std::array<U64, 16>& bitboards,
    std::vector<U16>& legalMoves) {
    /*
    appends all legal moves of the pawn on square to the legal moves vector
    */

    std::vector<U16> moves;

    if (square + 8 < 64 && !(bitboards[PIECES] & 1ULL << (square + 8))) {
        moves.push_back(square | (square + 8) << 6);
        if (square / 8 == 1 && !(bitboards[PIECES] & 1ULL << (square + 16))) {
            moves.push_back(square | (square + 16) << 6);
        }
    }
    if (square + 7 < 64 && square % 8 - 1 >= 0 && bitboards[BLACK_PIECES]
        & 1ULL << (square + 7)) {
        moves.push_back(square | (square + 7) << 6);
    }
    if (square + 9 < 64 && square % 8 + 1 < 8 && bitboards[BLACK_PIECES]
        & 1ULL << (square + 9)) {
        moves.push_back(square | (square + 9) << 6);
    }

    int promotionFlag = 0;
    if (square / 8 == 6) {
        promotionFlag = 3;
    }

    for (int i = 0; i < (int)moves.size(); i++) {
        for (int j = 0; j <= promotionFlag; j++) {
            legalMoves.push_back(moves[i] | j << 12);
        }
    }
}


void getBlackPawnMoves(int square, const std::array<U64, 16>& bitboards,
    std::vector<U16>& legalMoves) {
    /*
    appends all legal moves of the pawn on square to the legal moves vector
    */

    std::vector<U16> moves;

    if (square - 8 >= 0 && !(bitboards[PIECES] & 1ULL << (square - 8))) {
        moves.push_back(square | (square - 8) << 6);
        if (square / 8 == 6 && !(bitboards[PIECES] & 1ULL << (square - 16))) {
            moves.push_back(square | (square - 16) << 6);
        }
    }
    if (square - 9 >= 0 && square % 8 - 1 >= 0 && bitboards[WHITE_PIECES]
        & 1ULL << (square - 9)) {
        moves.push_back(square | (square - 9) << 6);
    }
    if (square - 7 >= 0 && square % 8 + 1 < 8 && bitboards[WHITE_PIECES]
        & 1ULL << (square - 7)) {
        moves.push_back(square | (square - 7) << 6);
    }

    int promotionFlag = 0;
    if (square / 8 == 1) {
        promotionFlag = 3;
    }

    for (int i = 0; i < (int)moves.size(); i++) {
        for (int j = 0; j <= promotionFlag; j++) {
            legalMoves.push_back(moves[i] | j << 12);
        }
    }
}


std::vector<U16> Chessboard::getLegalMoves() {
    /*
    returns all legal moves on the current position
    */

    std::vector<U16> legalMoves;

    if (turn) { // whites turn
        for (int sq = 0; sq < 64; sq++) {
            if (!(bitboards[PIECES] & 1ULL << sq)) {
                continue;
            }

            int piece = mailbox[sq];

            switch (piece) {
                case WHITE_PAWN: {
                    getWhitePawnMoves(sq, bitboards, legalMoves);
                    break;
                }

                case WHITE_KNIGHT: {
                    U64 moveMask = KNIGHT_LOOKUP[sq];
                    moveMask &= ~bitboards[WHITE_PIECES];
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_BISHOP: {
                    U64 moveMask = getBishopMask(sq, bitboards, magic,
                        WHITE_PIECES);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_ROOK: {
                    U64 moveMask = getRookMask(sq, bitboards, magic,
                        WHITE_PIECES);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case WHITE_QUEEN: {
                    U64 moveMask = getBishopMask(sq, bitboards, magic,
                        WHITE_PIECES) | getRookMask(sq, bitboards, magic,
                        WHITE_PIECES);
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
        for (int sq = 0; sq < 64; sq++) {
            if (!(bitboards[PIECES] & 1ULL << sq)) {
                continue;
            }

            int piece = mailbox[sq];

            switch (piece) {
                case BLACK_PAWN: {
                    getBlackPawnMoves(sq, bitboards, legalMoves);
                    break;
                }

                case BLACK_KNIGHT: {
                    U64 moveMask = KNIGHT_LOOKUP[sq];
                    moveMask &= ~bitboards[BLACK_PIECES];
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case BLACK_BISHOP: {
                    U64 moveMask = getBishopMask(sq, bitboards, magic,
                        BLACK_PIECES);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case BLACK_ROOK: {
                    U64 moveMask = getRookMask(sq, bitboards, magic,
                        BLACK_PIECES);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case BLACK_QUEEN: {
                    U64 moveMask = getBishopMask(sq, bitboards, magic,
                        BLACK_PIECES) | getRookMask(sq, bitboards, magic,
                        BLACK_PIECES);
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }

                case BLACK_KING: {
                    U64 moveMask = KING_LOOKUP[sq];
                    moveMask &= ~bitboards[BLACK_PIECES];
                    moveMaskToU16(sq, moveMask, legalMoves);
                    break;
                }
            }
        }
    }

    return legalMoves;
}
