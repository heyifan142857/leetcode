// Weekly Contest 497 - Q1
// Created automatically
// Created at 2026-04-12 09:40:41

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDegrees(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> ans(n, 0);
        for (int i = 0; i < n; ++i) {
            int deg = 0;
            for (int j = 0; j < (int)matrix[i].size(); ++j) deg += matrix[i][j];
            ans[i] = deg;
        }
        return ans;
    }
};