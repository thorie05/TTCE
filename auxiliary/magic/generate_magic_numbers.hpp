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


pair<U64, U64> findMagicNumber(int numberOfTrys,
    const unordered_map<U64, U64>& lookupTable) {
    /*
    finds a magic number for the given lookup table
    */

    int minShift = 50;

    int rightmostIndex = INT_MAX;
    int bestShift = 0;
    U64 bestMagicNumber = 0;

    // try n magic numbers and store the best result
    for (int i = 0; i < numberOfTrys; i++) {
        U64 magicNumber = randomFewNonzeroBits();

        int shift = minShift;
        int lastRight = 0;
        U64 right = 0;
        // increment the starting shift until the remapping is no longer valid
        while (true) {
            unordered_map<U64, U64> remapped;
            bool ok = true;

            // apply magic number and check if it creates a valid remapping
            for (auto& it: lookupTable) {
                U64 oldKey = it.first;
                U64 newKey = (oldKey * magicNumber) >> shift;

                if (remapped.find(newKey) != remapped.end()) {
                    // allow constructive collisions
                    if (remapped[newKey] != it.second) {
                        ok = false;
                        break;
                    }
                }
                remapped[newKey] = it.second;
                right = max(right, newKey); // note the rightmost remapped index
            }

            if (!ok) {
                // if magic number worked with min shift and better than best
                // shift make it new best magic number - favor magic numbers
                // where rightmost remapped index is as small as possible
                if (shift > minShift && ((shift - 1 > bestShift) ||
                    (shift - 1 == bestShift && lastRight < rightmostIndex))) {
                    bestShift = shift - 1;
                    bestMagicNumber = magicNumber;
                    rightmostIndex = lastRight;
                }
                break;
            }

            lastRight = right;
            right = 0;
            shift++;
        }
    }

    return make_pair(bestShift, bestMagicNumber);
}
