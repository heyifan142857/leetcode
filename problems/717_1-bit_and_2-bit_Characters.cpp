//
// Created by azote on 11/18/25.
//
#include <vector>
using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int> &bits) {
        int n = bits.size();

        int p = 0;

        while (p < n) {
            if (p == n - 1) {
                return true;
            }
            if (bits[p] == 1) {
                p += 2;
            } else {
                p++;
            }
        }

        return false;
    }
};
