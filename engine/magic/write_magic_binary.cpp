#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;

int main() {
    // read key value pairs

    ifstream finBishops("key_value_pairs_bishops.txt");
    ifstream finRooks("key_value_pairs_rooks.txt");

    // read number of lines 
    int numLinesBishops;
    finBishops >> numLinesBishops;
    int numLinesRooks;
    finRooks >> numLinesRooks;

    // key value arrays
    array<vector<U64>, 64> bishopKeys;
    array<vector<U64>, 64> bishopValues;
    array<vector<U64>, 64> rookKeys;
    array<vector<U64>, 64> rookValues;

    // read bishops
    for (int i = 0; i < numLinesBishops; i++) {
        int ind;
        U64 key, value;

        finBishops >> ind >> key >> value;
        bishopKeys[ind].push_back(key);
        bishopValues[ind].push_back(value);
    }

    // read rooks
    for (int i = 0; i < numLinesRooks; i++) {
        int ind;
        U64 key, value;

        finRooks >> ind >> key >> value;
        rookKeys[ind].push_back(key);
        rookValues[ind].push_back(value);
    }

    // read magic numbers and shifts

    ifstream finMagicBishops("magic_numbers_bishops.txt");
    ifstream finMagicRooks("magic_numbers_rooks.txt");

    array<U64, 64> magicNumbersBishops;
    array<U64, 64> shiftsBishops;
    array<U64, 64> magicNumbersRooks;
    array<U64, 64> shiftsRooks;

    // read bishops
    for (int i = 0; i < 64; i++) {
        finMagicBishops >> magicNumbersBishops[i];
    }
    for (int i = 0; i < 64; i++) {
        finMagicBishops >> shiftsBishops[i];
    }

    // read rooks
    for (int i = 0; i < 64; i++) {
        finMagicRooks >> magicNumbersRooks[i];
    }
    for (int i = 0; i < 64; i++) {
        finMagicRooks >> shiftsRooks[i];
    }

    int bishopLookupSize = 0;
    array<int, 64> bishopLookupIndex;
    for (int i = 0; i < 64; i++) {
        bishopLookupIndex[i] = bishopLookupSize;
        bishopLookupSize += 1 << (64 - shiftsBishops[i]);
    }

    int rookLookupSize = 0;
    array<int, 64> rookLookupIndex;
    for (int i = 0; i < 64; i++) {
        rookLookupIndex[i] = rookLookupSize;
        rookLookupSize += 1 << (64 - shiftsRooks[i]);
    }

    // make lookup arrays
    array<vector<U64>, 64> bishopLookup;
    array<vector<U64>, 64> rookLookup;

    for (int i = 0; i < 64; i++) {
        bishopLookup[i].resize(1 << (64 - shiftsBishops[i]));
        rookLookup[i].resize(1 << (64 - shiftsRooks[i]));

        for (int j = 0; j < bishopKeys[i].size(); j++) {
            U64 newIndex = (bishopKeys[i][j] * magicNumbersBishops[i]) >> shiftsBishops[i];
            bishopLookup[i][newIndex] = bishopValues[i][j];
        }

        for (int j = 0; j < rookKeys[i].size(); j++) {
            U64 newIndex = (rookKeys[i][j] * magicNumbersRooks[i]) >> shiftsRooks[i];
            rookLookup[i][newIndex] = rookValues[i][j];
        }
    }

    cout << "bishop lookup" << endl;
    for (int i = 0; i < 64; i++) {
        cout << i << ": ";
        cout << 64 - shiftsBishops[i] << " / " << log2(bishopKeys[i].size()) << endl;
        for (int j = 0; j < bishopLookup[i].size(); j++) {
            if (bishopLookup[i][j]) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }
    cout << endl;

    cout << "rook lookup" << endl;
    for (int i = 0; i < 64; i++) {
        cout << i << ": ";
        cout << 64 - shiftsRooks[i] << " / " << log2(rookKeys[i].size()) << endl;
        for (int j = 0; j < rookLookup[i].size(); j++) {
            if (rookLookup[i][j]) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    return 0;
}
