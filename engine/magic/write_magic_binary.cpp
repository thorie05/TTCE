#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;


void writeToBinary(std::string filename, std::array<U64, 64> magicNumbers,
    std::array<int, 64> shifts, std::array<U64, 64> masks,
    std::array<int, 64> lookupIndex, std::vector<U64> lookup) {

    std::ofstream file(filename, std::ios::binary);

    // write magic numbers
    for (const auto& value : magicNumbers) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(U64));
    }

    // write shifts
    for (const auto& value : shifts) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }

    // write masks
    for (const auto& value : masks) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(U64));
    }

    // write lookup index array
    for (const auto& value : lookupIndex) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }

    // write lookup array
    for (const auto& value : lookup) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(U64));
    }

    file.close();
}


int main() {

    // read masks
    ifstream finMasks("masks.txt");

    array<U64, 64> bishopMasks;
    array<U64, 64> rookMasks;
    for (int i = 0; i < 64; i++) {
        finMasks >> bishopMasks[i];
    }
    for (int i = 0; i < 64; i++) {
        finMasks >> rookMasks[i];
    }

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
    array<int, 64> shiftsBishops;
    array<U64, 64> magicNumbersRooks;
    array<int, 64> shiftsRooks;

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

    // calculate total size of bishop lookup array
    int bishopLookupSize = 0;
    array<int, 64> bishopLookupIndex;
    for (int i = 0; i < 64; i++) {
        bishopLookupIndex[i] = bishopLookupSize;
        bishopLookupSize += 1 << (64 - shiftsBishops[i]);
    }

    // calculate total size of rook lookup array
    int rookLookupSize = 0;
    array<int, 64> rookLookupIndex;
    for (int i = 0; i < 64; i++) {
        rookLookupIndex[i] = rookLookupSize;
        rookLookupSize += 1 << (64 - shiftsRooks[i]);
    }

    // make lookup arrays
    vector<U64> bishopLookup(bishopLookupSize);
    vector<U64> rookLookup(rookLookupSize);

    int currentIndexBishops = 0;
    int currentIndexRooks = 0;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < bishopKeys[i].size(); j++) {
            U64 newIndex = (bishopKeys[i][j] * magicNumbersBishops[i])
                >> shiftsBishops[i];
            bishopLookup[currentIndexBishops + newIndex] = bishopValues[i][j];
            currentIndexBishops++;
        }

        for (int j = 0; j < rookKeys[i].size(); j++) {
            U64 newIndex = (rookKeys[i][j] * magicNumbersRooks[i])
                >> shiftsRooks[i];
            rookLookup[currentIndexRooks + newIndex] = rookValues[i][j];
            currentIndexRooks++;
        }
    }

    cout << "size of lookup array bishops: " << bishopLookupSize << endl;
    cout << "size of lookup array rooks: " << rookLookupSize << endl;

    // relevant information
    // magic numbers 64
    // shifts 64
    // masks 64
    // lookup index for squares 64
    // lookup array

    // lookup array size -> needs to be hardcoded

    writeToBinary("bishop_magic.dat", magicNumbersBishops, shiftsBishops, 
        bishopMasks, bishopLookupIndex, bishopLookup);
    writeToBinary("rook_magic.dat", magicNumbersRooks, shiftsRooks, 
        rookMasks, rookLookupIndex, rookLookup);

    return 0;
}
