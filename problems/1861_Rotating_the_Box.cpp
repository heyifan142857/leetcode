// 1861. Rotating the Box
// Created automatically
// Created at 2026-05-06 09:26:07

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();
        vector<vector<char>> res(n, vector<char>(m, '.'));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
            {
                res[j][m - 1 - i] = boxGrid[i][j];
            }
            
        }

        for (int j = 0; j < m; j++) {
            int bottom = n;
            for (int i = n-1; i >= 0; i--) {
                if (res[i][j] == '.') {
                    continue;
                } else if (res[i][j] == '*') {
                    bottom = i;
                } else {
                    if (i < bottom - 1) {
                        res[bottom - 1][j] = '#';
                        res[i][j] = '.';
                    }
                    bottom--;
                }
            }
        }
        return res;
    }
};
