#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;

// init random number generator
random_device rd;
mt19937_64 eng(rd());
uniform_int_distribution<U64> distr;


U64 randomFewNonzeroBits() {
    /*
    generates random ULL with low number of nonzero bits
    */

    return distr(eng) & distr(eng) & distr(eng);
}


pair<U64, U64> findMagics(int n, int square, const array<vector<U64>, 64>& keys,
    const array<vector<U64>, 64>& values) {
    /*
    finds a magic number for the given square and the given keys and values
    */

    int startingShift = 50;
    int bestShift = 0;
    U64 bestMagicNumber = 0;

    // try n magic numbers and store the best result
    for (int i = 0; i < n; i++) {
        U64 magicNumber = randomFewNonzeroBits(); // random number

        int shift = startingShift;
        // increment the starting shift until the remapping is no longer valid
        while (true) {
            unordered_map<U64, U64> remapped;
            bool ok = true;

            // apply magic number and check if it creates a valid remapping
            for (int j = 0; j < keys[square].size(); j++) { 

                U64 oldIndex = keys[square][j];
                U64 newIndex = (oldIndex * magicNumber) >> shift;

                if (remapped.find(newIndex) != remapped.end()) {
                    // allow constructive collisions
                    if (remapped[newIndex] != values[square][j]) {
                        ok = false;
                        break;
                    }
                }
                remapped[newIndex] = values[square][j];
            }

            if (!ok) {
                if (shift > startingShift && shift - 1 > bestShift) {
                    bestShift = shift - 1;
                    bestMagicNumber = magicNumber;
                }
                break;
            }

            shift++;
        }
    }

    return make_pair(bestShift, bestMagicNumber);
}


int main() {
    cout.precision(2);

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

    int numberOfTrys = 100000;

    // find magic numbers and shifts for bishops
    cout << "bishops: " << endl;
    array<U64, 64> magicNumbersBishops;
    array<int, 64> shiftsBishops;
    for (int i = 0; i < 64; i++) {
        cout << i << endl;
        pair<U64, U64> magicResult = findMagics(numberOfTrys, i, bishopKeys,
            bishopValues);
        shiftsBishops[i] = magicResult.first;
        magicNumbersBishops[i] = magicResult.second;
    }

    // write to file
    ofstream foutBishops("magic_numbers_bishops.txt");
    for (int i = 0; i < 64; i++) {
        foutBishops << magicNumbersBishops[i] << " ";
    }
    foutBishops << endl;
    for (int i = 0; i < 64; i++) {
        foutBishops << shiftsBishops[i] << " ";
    }
    foutBishops.close();

    // find magic numbers and shifts for rooks
    cout << "rooks:" << endl;
    array<U64, 64> magicNumbersRooks;
    array<int, 64> shiftsRooks;
    for (int i = 0; i < 64; i++) {
        cout << i << endl;
        pair<U64, U64> magicResult = findMagics(numberOfTrys, i, rookKeys,
            rookValues);
        shiftsRooks[i] = magicResult.first;
        magicNumbersRooks[i] = magicResult.second;
    }

    // write to file
    ofstream foutRooks("magic_numbers_rooks.txt");
    for (int i = 0; i < 64; i++) {
        foutRooks << magicNumbersRooks[i] << " ";
    }
    foutRooks << endl;
    for (int i = 0; i < 64; i++) {
        foutRooks << shiftsRooks[i] << " ";
    }
    foutRooks.close();

    return 0;
}
