#include "chessboard.hpp"
#include "constants.hpp"
#include <string>
#include <sstream>
#include <array>


Chessboard::Chessboard(const std::string& fen) {
    /*
    initializes the board using the given fen string
    */

    for (int i = 0; i < 64; i++) {
        mailbox[i] = EMPTY_SQUARE;
    }

    for (int i = 0; i < (int)bitboards.size(); i++) {
        bitboards[i] = 0ULL;
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
        int piece;

        switch (currentChar) {
            case 'P':
                piece = WHITE_PAWN;
                break;
            case 'N':
                piece = WHITE_KNIGHT;
                break;
            case 'B':
                piece = WHITE_BISHOP;
                break;
            case 'R':
                piece = WHITE_ROOK;
                break;
            case 'Q':
                piece = WHITE_QUEEN;
                break;
            case 'K':
                piece = WHITE_KING;
                break;
            case 'p':
                piece = BLACK_PAWN;
                break;
            case 'n':
                piece = BLACK_KNIGHT;
                break;
            case 'b':
                piece = BLACK_BISHOP;
                break;
            case 'r':
                piece = BLACK_ROOK;
                break;
            case 'q':
                piece = BLACK_QUEEN;
                break;
            case 'k':
                piece = BLACK_KING;
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
            bitboards[piece] |= (1ULL << currentSquare);
            mailbox[currentSquare] = piece;
            currentSquare++;
        }
    }

    // calculate additional bitboards
    bitboards[WHITE_PIECES] = bitboards[WHITE_PAWN] | bitboards[WHITE_KNIGHT] 
        | bitboards[WHITE_BISHOP] | bitboards[WHITE_ROOK]
        | bitboards[WHITE_QUEEN] | bitboards[WHITE_KING];

    bitboards[BLACK_PIECES] = bitboards[BLACK_PAWN] | bitboards[BLACK_KNIGHT] 
        | bitboards[BLACK_BISHOP] | bitboards[BLACK_ROOK]
        | bitboards[BLACK_QUEEN] | bitboards[BLACK_KING];

    bitboards[PIECES] = bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES];

    // whites turn is true, blacks turn is false
    turn = splitFen[1] == "w" ? true : false;

    // assign castling rights
    for (int i = 0; i < (int)splitFen[2].length(); i++) {
        if (splitFen[2][i] == 'K') {
            whiteCastleKingside = true;
        }
        if (splitFen[2][i] == 'Q') {
            whiteCastleQueenside = true;
        }
        if (splitFen[2][i] == 'k') {
            blackCastleKingside = true;
        }
        if (splitFen[2][i] == 'q') {
            blackCastleKingside = true;
        }
    }

    // en passant square
    if (splitFen[3] == "-") { // no en passant square
        enPassantSquare = NONE_SQUARE;
    }
    else { // convert algebraic notation
        int file = splitFen[4][0] - 'a'; 
        int rank = splitFen[4][1] - '1';
        enPassantSquare = 8 * rank + file;
    }

    // initialize the half move clock
    halfmoveClock = stoi(splitFen[4]);

    // initialize the number of full moves
    turnNumber = stoi(splitFen[5]);
}
