#include "bits/stdc++.h"
using namespace std;

typedef unsigned long long U64;

random_device rd;
mt19937_64 eng(rd());
uniform_int_distribution<U64> distr;

U64 randomFewNonzeroBits() {
    U64 a = distr(eng);
    U64 b = distr(eng);
    U64 c = distr(eng);
    return a & b & c;
}

int main() {
    ifstream fin("../engine/magics_rook.txt");
    int numLines;
    fin >> numLines;

    vector<vector<U64>> keys;
    vector<vector<U64>> values;

    keys.resize(64);
    values.resize(64);
    for (int i = 0; i < numLines; i++) {
        int ind;
        U64 key, value;
        fin >> ind >> key >> value;
        keys[ind].push_back(key);
        values[ind].push_back(value);
    }

    vector<U64> magicNumbers(64);
    vector<int> shifts(64);
    int n = 20000; // number of tries with random number


    for (int i = 19; i < 20; i++) {

        int overallBestShift = 0;
        U64 bestMagicNumber = 69;

        for (int j = 0; j < n; j++) {

            U64 magicNumber = randomFewNonzeroBits();
            int bestShift;

            for (int k = 0; k < 64; k++) {
                set<U64> seen;
                bool ok = true;
                for (int l = 0; l < keys[i].size(); l++) { 
                    // test if there are collisions
                    U64 newIndex = keys[i][l];
                    newIndex *= magicNumber;
                    newIndex >>= k;

                    if (seen.find(newIndex) != seen.end()) { // if already seen
                        ok = false;
                        break;
                    }
                    seen.insert(newIndex);
                }
                if (!ok) {
                    bestShift = k - 1;
                    break;
                }
            }

            if (bestShift > overallBestShift) {
                overallBestShift = bestShift;
                bestMagicNumber = magicNumber;
            }
        }
        magicNumbers[i] = bestMagicNumber;
        shifts[i] = 64 - overallBestShift;
        cout << i << " " << shifts[i] << " " << magicNumbers[i] << endl;
    }

    return 0;
}