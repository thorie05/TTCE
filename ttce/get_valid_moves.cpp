#include "chessboard.hpp"
#include "attack_patterns.hpp"

#include <vector>
#include <tuple>


std::vector<std::tuple<int,int,std::string>> Chessboard::getValidMovesBitboard() {
    std::vector<std::tuple<int,int,std::string>> validMoves;

    if (turn == "w") {
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
    }
    else {

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
