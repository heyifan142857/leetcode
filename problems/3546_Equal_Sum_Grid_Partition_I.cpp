// 3546. Equal Sum Grid Partition I
// Created automatically
// Created at 2026-03-25 10:41:09

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        long long totalSum = 0;
        for (const auto& row : grid) {
            for (int num : row) {
                totalSum += num;    
            }
        }
        if (totalSum % 2 != 0) {
            return false;
        }
        long long target = totalSum / 2;
        
        long long colSum = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                colSum += grid[i][j];
            }
            if (colSum == target) {
                return true;
            }
            if (colSum > target) {
                break;
            }
        }
        
        long long rowSum = 0;
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                rowSum += grid[i][j];
            }
            if (rowSum == target) {
                return true;
            }
            if (rowSum > target) {
                break;
            }
        }

        return false;
    }
};