#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include <iostream>
#include <vector>

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

void printHexLookup(const std::vector<U64>& lookup) {
    /*
    prints the contents of a lookup array in hexadecimal and formats it
    */

    int tabSize = 4;
    int currentLineLength = tabSize;
    std::cout << "    ";
    for (int i = 0; i < lookup.size(); i++) {
        int nextLength = 4;
        if (lookup[i] > 0) {
            nextLength = 4 + log(lookup[i]) / log(16);
        }
        if (currentLineLength + 1 + nextLength > 80) {
            currentLineLength = tabSize;
            std::cout << std::endl << "    ";
        }
        if (currentLineLength != tabSize) {
            std::cout << " ";
            currentLineLength++;
        }
        currentLineLength += nextLength;
        std::cout << "0x" << std::hex << lookup[i] << ",";
    }
    std::cout << std::endl;
}

#endif
