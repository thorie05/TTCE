#include "chessboard.hpp"
#include "attack_patterns.hpp"

#include <vector>
#include <tuple>
#include <math.h>
#include <iostream>


std::vector<std::tuple<int,int,std::string>> getSlidingPieceMoves(int pos, const std::vector<int>& directions, Board bitboards) {
    std::vector<std::tuple<int,int,std::string>> moves;

    char color = bitboards.whitePieces & (1ULL << pos) ? 'w': 'b';
    if (color == 'b' && !(bitboards.blackPieces & (1ULL << pos))) {
        return moves;
    }

    for (int i = 0; i < (int)directions.size(); i++) {
        int distL = pos % 8;
        int distR = 7 - distL;
        int dist = (directions[i] == -1 || directions[i] == -9 || directions[i] == 7) ? distL : distR;
        if (abs(directions[i]) == 8) {
            dist = 8;
        }

        int currentPos = pos + directions[i];
        int j = 0;
        while (j < dist && currentPos >= 0 && currentPos < 64) {
            if (bitboards.whitePieces & (1ULL << currentPos) && color == 'w') break;
            if (bitboards.blackPieces & (1ULL << currentPos) && color == 'b') break;
            moves.push_back({pos, currentPos, ""});
            if (bitboards.blackPieces & (1ULL << currentPos) && color == 'w') break;
            if (bitboards.whitePieces & (1ULL << currentPos) && color == 'b') break;
            currentPos += directions[i];
            j++;
        }
    }

    return moves;
}


std::vector<std::tuple<int,int,std::string>> Chessboard::getValidMovesBitboard() {
    std::vector<std::tuple<int,int,std::string>> validMoves;

    if (turn == "w") { // get valid moves for white
        for (int i = 0; i < 64; i++) {
            if (bitboards.whitePawns & (1ULL << i)) {
                if (!(bitboards.pieces & (1ULL << (i + 8)))) {
                    validMoves.push_back({i, i + 8, ""});
                    if (!(bitboards.pieces & (1ULL << (i + 16))) && i / 8 == 1) {
                        validMoves.push_back({i, i + 16, ""});
                    }
                }
                if (bitboards.blackPieces & (1ULL << (i + 7)) && i % 8 != 0) {
                    validMoves.push_back({i, i + 7, ""});
                }
                if (bitboards.blackPieces & (1ULL << (i + 9)) && i % 8 != 7) {
                    validMoves.push_back({i, i + 9, ""});
                }
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.whiteKnights & (1ULL << i)) {
                U64 possibleKnightMoves = 0;
                possibleKnightMoves = knightPatterns[i] & ~bitboards.whitePieces;
                for (int j = 0; j < 64; j++) {
                    if (possibleKnightMoves & (1ULL << j)) {
                        validMoves.push_back({i, j, ""});
                    }
                }
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.whiteKing & (1ULL << i)) {
                U64 possibleKingMoves = 0;
                possibleKingMoves = kingPatterns[i] & ~bitboards.whitePieces;
                for (int j = 0; j < 64; j++) {
                    if (possibleKingMoves & (1ULL << j)) {
                        validMoves.push_back({i, j, ""});
                    }
                }

                if (i == 4 && !(bitboards.pieces & (1ULL << 1)) && !(bitboards.pieces & (1ULL << 2)) 
                    && !(bitboards.pieces & (1ULL << 3)) && castlingRights[1]) {

                    validMoves.push_back({4, 2, ""});
                }
                if (i == 4 && !(bitboards.pieces & (1ULL << 5)) && !(bitboards.pieces & (1ULL << 6)) && castlingRights[0]) {
                    validMoves.push_back({4, 6, ""});
                }

                break;
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.whiteBishops & (1ULL << i)) {
                std::vector<std::tuple<int,int,std::string>> bishopMoves = getSlidingPieceMoves(i, bishopDirections, bitboards);
                validMoves.insert(validMoves.end(), bishopMoves.begin(), bishopMoves.end());
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.whiteRooks & (1ULL << i)) {
                std::vector<std::tuple<int,int,std::string>> rookMoves = getSlidingPieceMoves(i, rookDirections, bitboards);
                validMoves.insert(validMoves.end(), rookMoves.begin(), rookMoves.end());
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.whiteQueens & (1ULL << i)) {
                std::vector<std::tuple<int,int,std::string>> queenMoves = getSlidingPieceMoves(i, queenDirections, bitboards);
                validMoves.insert(validMoves.end(), queenMoves.begin(), queenMoves.end());
            }
        }
    }

    else { // get valid moves for black
        for (int i = 0; i < 64; i++) {
            if (bitboards.blackPawns & (1ULL << i)) {
                if (!(bitboards.pieces & (1ULL << (i - 8)))) {
                    validMoves.push_back({i, i - 8, ""});
                    if (!(bitboards.pieces & (1ULL << (i - 16))) && i / 8 == 6) {
                        validMoves.push_back({i, i - 16, ""});
                    }
                }
                if (bitboards.whitePieces & (1ULL << (i - 7)) && i % 8 != 0) {
                    validMoves.push_back({i, i - 7, ""});
                }
                if (bitboards.whitePieces & (1ULL << (i - 9)) && i % 8 != 7) {
                    validMoves.push_back({i, i - 9, ""});
                }
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.blackKnights & (1ULL << i)) {
                U64 possibleKnightMoves = 0;
                possibleKnightMoves = knightPatterns[i] & ~bitboards.blackPieces;
                for (int j = 0; j < 64; j++) {
                    if (possibleKnightMoves & (1ULL << j)) {
                        validMoves.push_back({i, j, ""});
                    }
                }
            }

        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.blackKing & (1ULL << i)) {
                U64 possibleKingMoves = 0;
                possibleKingMoves = kingPatterns[i] & ~bitboards.blackPieces;
                for (int j = 0; j < 64; j++) {
                    if (possibleKingMoves & (1ULL << j)) {
                        validMoves.push_back({i, j, ""});
                    }
                }

                if (i == 60 && !(bitboards.pieces & (1ULL << 57)) && !(bitboards.pieces & (1ULL << 58)) && 
                    !(bitboards.pieces & (1ULL << 59)) && castlingRights[3]) {

                    validMoves.push_back({60, 58, ""});
                }
                if (i == 60 && !(bitboards.pieces & (1ULL << 61)) && !(bitboards.pieces & (1ULL << 62)) && castlingRights[2]) {
                    validMoves.push_back({60, 62, ""});
                }

                break;
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.blackBishops & (1ULL << i)) {
                std::vector<std::tuple<int,int,std::string>> bishopMoves = getSlidingPieceMoves(i, bishopDirections, bitboards);
                validMoves.insert(validMoves.end(), bishopMoves.begin(), bishopMoves.end());
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.blackRooks & (1ULL << i)) {
                std::vector<std::tuple<int,int,std::string>> rookMoves = getSlidingPieceMoves(i, rookDirections, bitboards);
                validMoves.insert(validMoves.end(), rookMoves.begin(), rookMoves.end());
            }
        }

        for (int i = 0; i < 64; i++) {
            if (bitboards.blackQueens & (1ULL << i)) {
                std::vector<std::tuple<int,int,std::string>> queenMoves = getSlidingPieceMoves(i, queenDirections, bitboards);
                validMoves.insert(validMoves.end(), queenMoves.begin(), queenMoves.end());
            }
        }
    }

    return validMoves;
}

std::vector<std::tuple<std::tuple<int,int>,std::tuple<int,int>,std::string>> Chessboard::getValidMovesCoordinates() {
    std::vector<std::tuple<std::tuple<int,int>,std::tuple<int,int>,std::string>> validMoves;

    std::vector<std::tuple<int,int,std::string>> validMovesBitboard = getValidMovesBitboard();
    for (int i = 0; i < (int)validMovesBitboard.size(); i++) {
        std::tuple<int,int,std::string> move = validMovesBitboard[i];
        int startSquare = std::get<0>(move);
        int endSquare = std::get<1>(move);
        std::string promotion = std::get<2>(move);

        validMoves.push_back({{startSquare % 8, startSquare / 8}, {endSquare % 8, endSquare / 8}, promotion});
    }

    return validMoves;
}

std::vector<std::string> Chessboard::getValidMovesAlgebraic() {
    std::vector<std::string> validMoves;
    return validMoves;
}
