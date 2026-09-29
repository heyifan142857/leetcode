// 2267. Check if There Is a Valid Parentheses String Path
// Created automatically
// Created at 2026-09-29 21:38:00

#include <vector>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<char>> &grid) {
        int m = grid.size(), n = grid[0].size();
        if ((m + n) % 2 == 0 || grid[0][0] == ')' ||
            grid[m - 1][n - 1] == '(') {
            return false;
        }

        vector vis(m, vector(n, vector<int8_t>((m + n + 1) / 2)));

        auto dfs = [&](this auto &&dfs, int x, int y, int c) -> bool {
            if (c > m - x + n - y - 1) {
                return false;
            }
            if (x == m - 1 && y == n - 1) { // 终点
                return c == 1;
            }

            if (vis[x][y][c]) {
                return false;
            }
            vis[x][y][c] = true;

            c += grid[x][y] == '(' ? 1 : -1;
            if (c < 0) { // 右括号比左括号还多
                return false;
            }
            return x < m - 1 && dfs(x + 1, y, c) ||
                   y < n - 1 && dfs(x, y + 1, c);
        };

        return dfs(0, 0, 0);
    }
};
