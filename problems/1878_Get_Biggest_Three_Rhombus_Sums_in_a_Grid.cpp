// 1878. Get Biggest Three Rhombus Sums in a Grid
// Created automatically
// Created at 2026-03-16 10:54:14
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dr(m, vector<int>(n, 0)); // down-right prefix
        vector<vector<int>> dl(m, vector<int>(n, 0)); // down-left prefix
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dr[i][j] = grid[i][j] + ((i > 0 && j > 0) ? dr[i-1][j-1] : 0);
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = n-1; j >= 0; --j) {
                dl[i][j] = grid[i][j] + ((i > 0 && j + 1 < n) ? dl[i-1][j+1] : 0);
            }
        }

        set<int> s;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                s.insert(grid[i][j]);
                for (int k = 1; i - k >= 0 && i + k < m && j - k >= 0 && j + k < n; ++k) {
                    long long sum = 0;
                    // top -> right along down-right diagonal: (i-k, j) -> (i, j+k)
                    int r1 = i - k, c1 = j, r2 = i, c2 = j + k;
                    int seg1 = dr[r2][c2] - ((r1 > 0 && c1 > 0) ? dr[r1-1][c1-1] : 0);
                    sum += seg1;
                    // right -> bottom along down-left diagonal: (i, j+k) -> (i+k, j)
                    r1 = i; c1 = j + k; r2 = i + k; c2 = j;
                    int seg2 = dl[r2][c2] - ((r1 > 0 && c1 + 1 < n) ? dl[r1-1][c1+1] : 0);
                    sum += seg2;
                    // bottom -> left along down-right diagonal: (i, j-k) -> (i+k, j)
                    r1 = i; c1 = j - k; r2 = i + k; c2 = j;
                    int seg3 = dr[r2][c2] - ((r1 > 0 && c1 > 0) ? dr[r1-1][c1-1] : 0);
                    sum += seg3;
                    // left -> top along down-left diagonal: (i-k, j) -> (i, j-k)
                    r1 = i - k; c1 = j; r2 = i; c2 = j - k;
                    int seg4 = dl[r2][c2] - ((r1 > 0 && c1 + 1 < n) ? dl[r1-1][c1+1] : 0);
                    sum += seg4;
                    // corners were counted twice (each belongs to two segments), subtract them once
                    sum -= grid[i-k][j];
                    sum -= grid[i][j+k];
                    sum -= grid[i+k][j];
                    sum -= grid[i][j-k];
                    s.insert((int)sum);
                }
            }
        }

        vector<int> ans;
        for (auto it = s.rbegin(); it != s.rend() && ans.size() < 3; ++it) ans.push_back(*it);
        return ans;
    }
};