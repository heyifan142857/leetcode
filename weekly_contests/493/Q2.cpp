// Weekly Contest 493 - Q2
// Created automatically
// Created at 2026-03-21 16:21:44

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countCommas(long long n) {
        long long res = 0;
        long long L = 1000; // smallest number with 1 comma
        int k = 1; // number of commas for current range
        while (L <= n) {
            long long U = L * 1000 - 1; // largest number with k commas
            long long hi = (n < U) ? n : U;
            res += (hi - L + 1) * 1LL * k;
            if (L > LLONG_MAX / 1000) break;
            L *= 1000;
            ++k;
        }
        return res;
    }
};