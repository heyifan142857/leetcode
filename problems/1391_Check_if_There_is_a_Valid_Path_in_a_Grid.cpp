// 1391. Check if There is a Valid Path in a Grid
// Created automatically
// Created at 2026-04-27 14:46:14

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // directions: up, down, left, right
        // encoded as delta row, delta col
        vector<pair<int,int>> deltas = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        // For each street type, which directions it opens to
        // 0=up, 1=down, 2=left, 3=right
        vector<vector<bool>> open(7, vector<bool>(4, false));
        // street 1: left-right
        open[1][2] = open[1][3] = true;
        // street 2: up-down
        open[2][0] = open[2][1] = true;
        // street 3: left-down
        open[3][2] = open[3][1] = true;
        // street 4: right-down
        open[4][3] = open[4][1] = true;
        // street 5: left-up
        open[5][2] = open[5][0] = true;
        // street 6: right-up
        open[6][3] = open[6][0] = true;

        // opposite direction
        vector<int> opp = {1, 0, 3, 2};

        vector<vector<bool>> vis(m, vector<bool>(n, false));
        queue<pair<int,int>> q;
        q.push({0, 0});
        vis[0][0] = true;

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            if (r == m-1 && c == n-1) return true;

            int s = grid[r][c];
            for (int d = 0; d < 4; ++d) {
                if (!open[s][d]) continue;
                int nr = r + deltas[d].first;
                int nc = c + deltas[d].second;
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                if (vis[nr][nc]) continue;
                int ns = grid[nr][nc];
                if (!open[ns][opp[d]]) continue;
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }
        return false;
    }
};
