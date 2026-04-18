// 3783. Mirror Distance of an Integer
// Created automatically
// Created at 2026-04-18 14:38:44

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mirrorDistance(int n) {
        int reversed_n = 0, temp = n;
        while (temp > 0) {
            reversed_n = reversed_n * 10 + temp % 10;
            temp /= 10;
        }
        return abs(n - reversed_n);
    }
};