// 1886. Determine Whether Matrix Can Be Obtained By Rotation
// Created automatically
// Created at 2026-03-22 11:42:18

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        for (int rot = 0; rot < 4; ++rot) {
            bool same = true;
            for (int i = 0; i < n && same; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (mat[i][j] != target[i][j]) { same = false; break; }
                }
            }
            if (same) return true;

            // rotate mat by 90 degrees clockwise
            vector<vector<int>> t(n, vector<int>(n));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    t[j][n - 1 - i] = mat[i][j];
                }
            }
            mat.swap(t);
        }
        return false;
    }
};