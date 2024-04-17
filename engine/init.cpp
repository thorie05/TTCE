#include "chessboard.hpp"
#include "constants.hpp"
#include <string>
#include <sstream>
#include <array>


Chessboard::Chessboard(const std::string& fen): inputFen(fen) {
    // initializes the board using the given fen string

    for (int i = 0; i < 64; i++) {
        board.mailbox[i] = EMPTY_SQUARE;
    }

    // split fen by spaces
    std::string s;
    std::stringstream ss(fen);
    std::array<std::string,6> splitFen;
    for (int i = 0; i < 6; i++) {
        std::getline(ss, s, ' ');
        splitFen[i] = s;
    }

    // fill bitboards and mailbox array
    int currentSquare = 56;
    for (int i = 0; i < (int)splitFen[0].length(); i++) {
        char currentChar = splitFen[0][i];

        bool isPiece = true;
        int index;

        switch (currentChar) {
            case 'P':
                index = WHITE_PAWN;
                break;
            case 'N':
                index = WHITE_KNIGHT;
                break;
            case 'B':
                index = WHITE_BISHOP;
                break;
            case 'R':
                index = WHITE_ROOK;
                break;
            case 'Q':
                index = WHITE_QUEEN;
                break;
            case 'K':
                index = WHITE_KING;
                break;
            case 'p':
                index = BLACK_PAWN;
                break;
            case 'n':
                index = BLACK_KNIGHT;
                break;
            case 'b':
                index = BLACK_BISHOP;
                break;
            case 'r':
                index = BLACK_ROOK;
                break;
            case 'q':
                index = BLACK_QUEEN;
                break;
            case 'k':
                index = BLACK_KING;
                break;
            case '/': // new rank
                currentSquare -= 16;
                isPiece = false;
                break;
            default: // digit
                if (isdigit(currentChar)) {
                    currentSquare += currentChar - '0';
                }
                isPiece = false;
                break;
        }

        if (isPiece) {
            board.bitboards[index] |= (1ULL << currentSquare);
            board.mailbox[currentSquare] = index;
            currentSquare++;
        }
    }

    // calculate additional bitboards
    board.bitboards[12] = board.bitboards[0] | board.bitboards[1] 
        | board.bitboards[2] | board.bitboards[3] | board.bitboards[4] 
        | board.bitboards[5];

    board.bitboards[13] = board.bitboards[6] | board.bitboards[7] 
        | board.bitboards[8] | board.bitboards[9] | board.bitboards[10] 
        | board.bitboards[11];

    board.bitboards[14] = board.bitboards[12] | board.bitboards[13];

    // whites turn is true, blacks turn is false
    board.turn = splitFen[1] == "w" ? true : false;

    // assign castling rights
    for (int i = 0; i < (int)splitFen[2].length(); i++) {
        if (splitFen[2][i] == 'K') {
            board.whiteCastleKingside = true;
        }
        if (splitFen[2][i] == 'Q') {
            board.whiteCastleQueenside = true;
        }
        if (splitFen[2][i] == 'k') {
            board.blackCastleKingside = true;
        }
        if (splitFen[2][i] == 'q') {
            board.blackCastleKingside = true;
        }
    }

    // en passant square
    if (splitFen[3] == "-") { // no en passant square
        board.enPassantSquare = 64;
    }
    else { // convert algebraic notation
        int file = splitFen[4][0] - 'a'; 
        int rank = splitFen[4][1] - '1';
        board.enPassantSquare = 8 * rank + file;
    }

    // initialize the half move clock
    board.halfmoveClock = stoi(splitFen[4]);

    // initialize the number of full moves
    board.turnNumber = stoi(splitFen[5]);
}
