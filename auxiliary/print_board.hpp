#ifndef PRINT_BOARD_HPP
#define PRINT_BOARD_HPP

#include <iostream>

typedef unsigned long long U64;


void printBoard(const U64& board) {
    /*
    prints a board given in bitboard representation
    */

    for (int i = 56; i >= 0; i++) {
        if (board & 1ULL << i) {
            std::cout << 1;
        }
        else {
            std::cout << 0;
        }
        if ((i + 1) % 8 == 0) {
            i -= 16;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

#endif
