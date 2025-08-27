//
// Created by user on 2025/8/27.
//

#include <vector>
#include <functional>
#include <cstring>
#include <cmath>
using namespace std;

//官方题解
class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int dirs[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        int memo[m][n][4][2];
        memset(memo, -1, sizeof(memo));

        function<int(int, int, int, bool, int)> dfs = [&](int cx, int cy, int direction, bool turn, int target) -> int {
            int nx = cx + dirs[direction][0];
            int ny = cy + dirs[direction][1];
            /* 如果超出边界或者下一个节点值不是目标值，则返回 */
            if (nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != target) {
                return 0;
            }
            if (memo[nx][ny][direction][turn] != -1) {
                return memo[nx][ny][direction][turn];
            }

            /* 按照原来的方向继续行走 */
            int maxStep = dfs(nx, ny, direction, turn, 2 - target);
            if (turn) {
                /* 顺时针旋转 90 度转向 */
                maxStep = fmax(maxStep, dfs(nx, ny, (direction + 1) % 4, false, 2 - target));
            }
            memo[nx][ny][direction][turn] = maxStep + 1;
            return maxStep + 1;
        };

        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    for (int direction = 0; direction < 4; ++direction) {
                        res = fmax(res, dfs(i, j, direction, true, 2) + 1);
                    }
                }
            }
        }

        return res;
    }
};


//时间超限
//class Solution {
//    vector<pair<int, int>> directions = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
//    vector<vector<vector<vector<int>>>> memo;
//    vector<vector<int>> Grid;
//
//    int dfs(int x, int y, int dir, int turn, int target) {
//        int nx = x + directions[dir].first;
//        int ny = y + directions[dir].second;
//
//        if (nx < 0 || ny < 0 || nx >= Grid.size() || ny >= Grid[0].size() || Grid[nx][ny] != target) {
//            return 1;
//        }
//
//
//        if (memo[nx][ny][dir][turn] != -1) {
//            return memo[nx][ny][dir][turn]+1;
//        }
//
//        int rest_len = dfs(nx, ny, dir, turn, 2-target);
//
//        if (turn > 0) {
//            int new_dir = (dir + 1) % 4;
//            rest_len = max(rest_len, dfs(nx, ny, new_dir, turn - 1, 2-target));
//        }
//
//        memo[nx][ny][dir][turn] = rest_len;
//        return rest_len+1;
//    }
//
//public:
//    int lenOfVDiagonal(vector<vector<int>>& grid) {
//        if (grid.empty() || grid[0].empty()) return 0;
//
//        int m = grid.size(), n = grid[0].size();
//        int max_path = 0;
//
//        memo.resize(
//                m, vector<vector<vector<int>>>(
//                        n, vector<vector<int>>(
//                                4, vector<int>(2, -1))));
//        Grid = grid;
//
//        for (int i = 0; i < m; ++i) {
//            for (int j = 0; j < n; ++j) {
//                if (grid[i][j] == 1) {
//                    for (int dir = 0; dir < 4; ++dir) {
//                        max_path = max(max_path, dfs(i, j, dir, 1, 2));
//                    }
//                }
//            }
//        }
//
//        return max_path;
//    }
//};
