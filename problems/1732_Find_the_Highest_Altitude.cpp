// 1732. Find the Highest Altitude
// Created automatically
// Created at 2026-06-19 13:24:48

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int curr = 0;
        int maxAlt = 0;
        for (int g : gain) {
            curr += g;
            maxAlt = max(maxAlt, curr);
        }
        return maxAlt;
    }
};