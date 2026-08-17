// 2029. Stone Game IX
// Created automatically
// Created at 2026-08-16 20:53:16

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool stoneGameIX(vector<int> &stones) {
        int count[3] = {};
        for (int stone : stones) {
            ++count[stone % 3];
        }

        if (count[0] % 2 == 0) {
            return count[1] > 0 && count[2] > 0;
        }
        return abs(count[1] - count[2]) > 2;
    }
};
