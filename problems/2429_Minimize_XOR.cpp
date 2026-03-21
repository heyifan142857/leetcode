// 2429. Minimize XOR
// Created automatically
// Created at 2026-03-21 20:38:53

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int bitsNeeded = __builtin_popcount(num2);
        int result = 0;

        for (int bit = 30; bit >= 0 && bitsNeeded > 0; --bit) {
            if ((num1 >> bit) & 1) {
                result |= (1 << bit);
                --bitsNeeded;
            }
        }

        for (int bit = 0; bit <= 30 && bitsNeeded > 0; ++bit) {
            if (((result >> bit) & 1) == 0) {
                result |= (1 << bit);
                --bitsNeeded;
            }
        }

        return result;
    }
};
