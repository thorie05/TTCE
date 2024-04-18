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


void findMagics(int n, const array<vector<U64>, 64>& keys,
    const array<vector<U64>, 64>& values, array<U64, 64>& magicNumbers,
    array<int, 64>& shifts) {
    /*
    finds magic numbers for the given keys and values
    */

   // loop over every square
    for (int i = 0; i < 64; i++) {
        cout << 100 * i / 64.0 << "%" << endl;

        int bestShift = 0;
        U64 bestMagicNumber;

        // try n magic numbers and store the best
        for (int j = 0; j < n; j++) {

            U64 magicNumber = randomFewNonzeroBits();
            int shift;

            // try ignoring more and more bits until threre is a collision
            for (int k = 50; k < 64; k++) {
                unordered_map<U64, U64> remapped;
                bool uniqueIndices = true;

                // apply magic number and check if it creates a valid remapping
                for (int l = 0; l < keys[i].size(); l++) { 

                    U64 oldIndex = keys[i][l];
                    U64 newIndex = (oldIndex * magicNumber) >> k;

                    if (remapped.find(newIndex) != remapped.end()) {
                        // allow constructive collisions
                        if (remapped[newIndex] != values[i][l]) {
                            uniqueIndices = false;
                            break;
                        }
                    }
                    remapped[newIndex] = values[i][l];
                }
                if (!uniqueIndices) {
                    shift = k - 1; // best valid shift with the given number
                    break;
                }
            }

            if (shift > bestShift) { // store best shift and magic number
                bestShift = shift;
                bestMagicNumber = magicNumber;
            }
        }
        magicNumbers[i] = bestMagicNumber;
        shifts[i] = bestShift;
    }
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

    int numberOfMagicTrys = 100000;

    // find magic numbers and shifts for bishops
    cout << "bishops: " << endl;
    array<U64, 64> magicNumbersBishops;
    array<int, 64> shiftsBishops;
    findMagics(numberOfMagicTrys, bishopKeys, bishopValues, magicNumbersBishops, 
        shiftsBishops);

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
    findMagics(numberOfMagicTrys, rookKeys, rookValues, magicNumbersRooks, 
        shiftsRooks);

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
