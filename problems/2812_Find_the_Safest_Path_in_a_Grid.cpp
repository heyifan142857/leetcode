// 2812. Find the Safest Path in a Grid
// Created automatically
// Created at 2026-07-01 16:19:09

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        if (q.empty())
            return 2 * n;

        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        vector<vector<int>> best(n, vector<int>(n, -1));
        priority_queue<pair<int, pair<int, int>>> pq;
        pq.push({dist[0][0], {0, 0}});
        best[0][0] = dist[0][0];

        while (!pq.empty()) {
            auto [safe, pos] = pq.top();
            pq.pop();
            auto [r, c] = pos;
            if (safe != best[r][c])
                continue;
            if (r == n - 1 && c == n - 1)
                return safe;
            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                    continue;
                int ns = min(safe, dist[nr][nc]);
                if (ns > best[nr][nc]) {
                    best[nr][nc] = ns;
                    pq.push({ns, {nr, nc}});
                }
            }
        }

        return 0;
    }
};
