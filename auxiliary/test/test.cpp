#include "bits/stdc++.h"
#include "chessboard.hpp"
using namespace std;

Chessboard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

int search(int depth) {
    if (depth == 0) return 1;
    vector<Move> legalMoves = board.getLegalMoves();
    int s = 0;
    for (int i = 0; i < legalMoves.size(); i++) {
        board.move(legalMoves[i]);
        s += search(depth - 1);
        board.unmakeMove();
    }
    return s;
}

int main() {
    for (int i = 1; i < 7; i++) {
        cout << i << " " << search(i) << endl;
    }

    return 0;
}