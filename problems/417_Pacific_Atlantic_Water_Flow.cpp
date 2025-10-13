//
// Created by user on 2025/10/5.
//
#include <vector>
using namespace std;

class Solution {
public:
    int m, n;
    vector<vector<int>> heights;
    vector<vector<bool>> pacific, atlantic;
    const vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    void dfs(int r, int c, vector<vector<bool>> &ocean) {
        ocean[r][c] = true;
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            // 越界判断 + 未访问 + 高度合法（只能向高处或等高处“爬”）
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            if (ocean[nr][nc]) continue;
            if (heights[nr][nc] < heights[r][c]) continue;
            dfs(nr, nc, ocean);
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& h) {
        heights = h;
        m = h.size();
        n = h[0].size();
        pacific.assign(m, vector<bool>(n, false));
        atlantic.assign(m, vector<bool>(n, false));

        // 从两大洋的边界出发做 DFS
        for (int i = 0; i < m; ++i) {
            dfs(i, 0, pacific);          // 太平洋左边界
            dfs(i, n - 1, atlantic);     // 大西洋右边界
        }
        for (int j = 0; j < n; ++j) {
            dfs(0, j, pacific);          // 太平洋上边界
            dfs(m - 1, j, atlantic);     // 大西洋下边界
        }

        // 结果：同时能到达两大洋的格子
        vector<vector<int>> res;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};

