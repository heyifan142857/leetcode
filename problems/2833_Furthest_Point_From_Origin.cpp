// 2833. Furthest Point From Origin
// Created automatically
// Created at 2026-04-25 15:22:01

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int left = 0;
        int right = 0;
        int freeMove = 0;
        for (char c : moves) {
            if (c == 'L') {
                ++left;
            } else if (c == 'R') {
                ++right;
            } else {
                ++freeMove;
            }
        }
        return abs(left - right) + freeMove;
    }
};
