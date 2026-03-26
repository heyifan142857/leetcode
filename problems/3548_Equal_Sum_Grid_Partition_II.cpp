// 3548. Equal Sum Grid Partition II
// Created automatically
// Created at 2026-03-26 10:11:54

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasValue(const unordered_map<int, int>& freq, long long target) {
        if (target <= 0 || target > INT_MAX) {
            return false;
        }
        auto it = freq.find(static_cast<int>(target));
        return it != freq.end() && it->second > 0;
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        long long total = 0;
        vector<long long> rowSum(m, 0), colSum(n, 0);
        unordered_map<int, int> allFreq;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = grid[i][j];
                total += val;
                rowSum[i] += val;
                colSum[j] += val;
                ++allFreq[val];
            }
        }

        auto canRemoveHorizontal = [&](long long target, int topRow, int bottomRow,
                                       const unordered_map<int, int>& freq) -> bool {
            int height = bottomRow - topRow + 1;
            if (height == 1 && n == 1) {
                return false;
            }
            if (height > 1 && n > 1) {
                return hasValue(freq, target);
            }
            if (height == 1) {
                return grid[topRow][0] == target || grid[topRow][n - 1] == target;
            }
            return grid[topRow][0] == target || grid[bottomRow][0] == target;
        };

        auto canRemoveVertical = [&](long long target, int leftCol, int rightCol,
                                     const unordered_map<int, int>& freq) -> bool {
            int width = rightCol - leftCol + 1;
            if (m == 1 && width == 1) {
                return false;
            }
            if (m > 1 && width > 1) {
                return hasValue(freq, target);
            }
            if (width == 1) {
                return grid[0][leftCol] == target || grid[m - 1][leftCol] == target;
            }
            return grid[0][leftCol] == target || grid[0][rightCol] == target;
        };

        unordered_map<int, int> topFreq, bottomFreq = allFreq;
        long long topSum = 0;
        for (int cut = 0; cut < m - 1; ++cut) {
            topSum += rowSum[cut];
            for (int j = 0; j < n; ++j) {
                int val = grid[cut][j];
                ++topFreq[val];
                if (--bottomFreq[val] == 0) {
                    bottomFreq.erase(val);
                }
            }

            long long bottomSum = total - topSum;
            if (topSum == bottomSum) {
                return true;
            }

            if (topSum > bottomSum) {
                if (canRemoveHorizontal(topSum - bottomSum, 0, cut, topFreq)) {
                    return true;
                }
            } else {
                if (canRemoveHorizontal(bottomSum - topSum, cut + 1, m - 1, bottomFreq)) {
                    return true;
                }
            }
        }

        unordered_map<int, int> leftFreq, rightFreq = allFreq;
        long long leftSum = 0;
        for (int cut = 0; cut < n - 1; ++cut) {
            leftSum += colSum[cut];
            for (int i = 0; i < m; ++i) {
                int val = grid[i][cut];
                ++leftFreq[val];
                if (--rightFreq[val] == 0) {
                    rightFreq.erase(val);
                }
            }

            long long rightSum = total - leftSum;
            if (leftSum == rightSum) {
                return true;
            }

            if (leftSum > rightSum) {
                if (canRemoveVertical(leftSum - rightSum, 0, cut, leftFreq)) {
                    return true;
                }
            } else {
                if (canRemoveVertical(rightSum - leftSum, cut + 1, n - 1, rightFreq)) {
                    return true;
                }
            }
        }

        return false;
    }
};
