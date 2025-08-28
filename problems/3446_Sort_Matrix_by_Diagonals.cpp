//
// Created by user on 2025/8/28.
//

#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> decreasing = vector(n, vector<int>());
        vector<vector<int>> increasing = vector(n-1, vector<int>());

        for (int i = 0; i < n; ++i) {
            int x = i;
            int y = 0;
            while (x>=0 && x<n && y>=0 && y<n){
                decreasing[i].push_back(grid[x][y]);
                x++;
                y++;
            }
        }
        for (int i = 1; i < n; ++i) {
            int x = 0;
            int y = i;
            while (x>=0 && x<n && y>=0 && y<n){
                increasing[i-1].push_back(grid[x][y]);
                x++;
                y++;
            }
        }

        for (int i = 0; i < n; ++i) {
            sort(decreasing[i].begin(), decreasing[i].end(), greater<>());
        }

        for (int i = 0; i < n-1; ++i) {
            sort(increasing[i].begin(), increasing[i].end());
        }

        vector<vector<int>> ans = vector(n, vector(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < decreasing[i].size(); ++j) {
                ans[i+j][j] = decreasing[i][j];
            }
        }

        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j < increasing[i].size(); ++j) {
                ans[j][1+i+j] = increasing[i][j];
            }
        }

        return ans;
    }
};