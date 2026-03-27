// 2946. Matrix Similarity After Cyclic Shifts
// Created automatically
// Created at 2026-03-27 10:13:11

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        k = k % n;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int offset = (i % 2 != 0) ? k : (n - k);
                if (mat[i][j] != mat[i][(j + offset) % n]) {
                    return false;
                }
            }
        }
        return true;
    }
};