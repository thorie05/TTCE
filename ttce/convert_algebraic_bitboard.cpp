#include "chessboard.hpp"

#include <string>

int algebraicToBitboardSquare(std::string algebraicSquare) {
    int file = algebraicSquare[0] - 'a'; 
    int rank = algebraicSquare[1] - '1';

    return 8 * rank + file;
}

std::string bitboardToAlgebraicSquare(int bitboardSquare) {
    char file = bitboardSquare % 8 + 'a';
    char rank = bitboardSquare / 8 + '1';

    return std::string() + file + rank;
}
