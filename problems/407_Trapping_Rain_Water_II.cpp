//
// Created by user on 2025/10/3.
//
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m == 0) return 0;
        int n = heightMap[0].size();
        if (n == 0) return 0;

        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; ++i) {
            pq.emplace(heightMap[i][0], i, 0);
            pq.emplace(heightMap[i][n-1], i, n-1);
            visited[i][0] = visited[i][n-1] = true;
        }
        for (int j = 0; j < n; ++j) {
            pq.emplace(heightMap[0][j], 0, j);
            pq.emplace(heightMap[m-1][j], m-1, j);
            visited[0][j] = visited[m-1][j] = true;
        }

        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        int water = 0;

        while (!pq.empty()) {
            auto [h, x, y] = pq.top(); pq.pop();

            for (auto& d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny]) continue;

                visited[nx][ny] = true;
                if (heightMap[nx][ny] < h) {
                    water += h - heightMap[nx][ny];
                    pq.emplace(h, nx, ny);
                } else {
                    pq.emplace(heightMap[nx][ny], nx, ny);
                }
            }
        }
        return water;
    }
};
