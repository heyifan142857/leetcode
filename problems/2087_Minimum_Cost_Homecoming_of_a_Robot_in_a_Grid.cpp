// 2087. Minimum Cost Homecoming of a Robot in a Grid
// Created automatically
// Created at 2026-04-04 13:11:24

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        long long cost = 0;
        int sr = startPos[0], sc = startPos[1];
        int hr = homePos[0], hc = homePos[1];

        if (sr < hr) {
            for (int r = sr + 1; r <= hr; ++r) cost += rowCosts[r];
        } else if (sr > hr) {
            for (int r = hr; r <= sr - 1; ++r) cost += rowCosts[r];
        }

        if (sc < hc) {
            for (int c = sc + 1; c <= hc; ++c) cost += colCosts[c];
        } else if (sc > hc) {
            for (int c = hc; c <= sc - 1; ++c) cost += colCosts[c];
        }

        return (int)cost;
    }
};