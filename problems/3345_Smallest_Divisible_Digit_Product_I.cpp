// 3345. Smallest Divisible Digit Product I
// Created automatically
// Created at 2026-08-06 14:59:22

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestNumber(int n, int t) {
        while (true) {
            int x = n;
            int product = 1;

            while (x > 0) {
                product *= x % 10;
                x /= 10;
            }

            if (product % t == 0) {
                return n;
            }

            n++;
        }
    }
};
