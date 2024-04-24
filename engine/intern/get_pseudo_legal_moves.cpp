#include "chessboard.hpp"
#include "constants.hpp"
#include "position.hpp"
#include "magic_info.hpp"
#include <iostream>
#include <tuple>


void getWhitePawnMoves(int square, const Position& board,
    std::vector<U16>& pseudoLegalMoves) {
    /*
    calculates pseudo legal moves for the white pawn on square
    */

    if (!(board.bitboards[PIECES] & 1ULL<<(square + 8))) {
        // move one square forward
        pseudoLegalMoves.push_back(square | (square + 8) << 6);
        if (!(board.bitboards[PIECES] & 1ULL<<(square + 16)) && square >= 8
            && square <= 15) {
            // move two squares forward
            pseudoLegalMoves.push_back(square | (square + 16) << 6);
        }
    }
}


void getBishopMoves(int square, const Position& board, const MagicInfo& magic,
    std::vector<U16>& pseudoLegalMoves) {
    /*
    calculates pseudo legal moves for the bishop on square
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

    // convert move bitboard to U16 format
    for (int j = 0; j < 64; j++) {
        if (moveMask & 1ULL << j) {
            pseudoLegalMoves.push_back(square | j << 6);
        }
    }
}


void getRookMoves(int square, const Position& board, const MagicInfo& magic,
    std::vector<U16>& pseudoLegalMoves) {
    /*
    calculates pseudo legal moves for the rook on square
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

    // convert move bitboard to U16 format
    for (int j = 0; j < 64; j++) {
        if (moveMask & 1ULL << j) {
            pseudoLegalMoves.push_back(square | j << 6);
        }
    }
}


void getQueenMoves(int square, const Position& board, const MagicInfo& magic,
    std::vector<U16>& pseudoLegalMoves) {
    /*
    calculates pseudo legal moves for the queen on square
    */

    // calculate bishop lookup key
    U64 bishopKey = board.bitboards[PIECES] & magic.bishopMasks[square];
    bishopKey *= magic.bishopMagicNumbers[square];
    bishopKey >>= magic.bishopShifts[square];
    bishopKey += magic.bishopLookupIndex[square];

    // calculate rook lookup key
    U64 rookKey = board.bitboards[PIECES] & magic.rookMasks[square];
    rookKey *= magic.rookMagicNumbers[square];
    rookKey >>= magic.rookShifts[square];
    rookKey += magic.rookLookupIndex[square];

    // get moves using that key
    U64 bishopMoveMask = magic.bishopLookup[bishopKey];
    U64 rookMoveMask = magic.rookLookup[rookKey];

    // combine bishop and rook move mask
    U64 moveMask = bishopMoveMask | rookMoveMask;

    // remove friendly pieces
    moveMask &= ~board.bitboards[WHITE_PIECES];

    // convert move bitboard to U16 format
    for (int j = 0; j < 64; j++) {
        if (moveMask & 1ULL << j) {
            pseudoLegalMoves.push_back(square | j << 6);
        }
    }
}


std::vector<U16> Chessboard::getPseudoLegalMoves() {
    std::vector<U16> pseudoLegalMoves;
    /*
    returns all pseudo legal moves on the current position
    */

    if (board.turn) { // whites turn
        for (int sq = 0; sq < 64; sq++) {
            int piece = board.mailbox[sq];

            switch (piece) {
                case WHITE_PAWN: {
                    // needs promotion
                    getWhitePawnMoves(sq, board, pseudoLegalMoves);
                    break;
                }

                case WHITE_BISHOP: {
                    getBishopMoves(sq, board, magic, pseudoLegalMoves);
                    break;
                }

                case WHITE_ROOK: {
                    getRookMoves(sq, board, magic, pseudoLegalMoves);
                    break;
                }

                case WHITE_QUEEN: {
                    getQueenMoves(sq, board, magic, pseudoLegalMoves);
                    break;
                }
            }
        }
    }
    else { // blacks turn

    }

    return pseudoLegalMoves;
}
