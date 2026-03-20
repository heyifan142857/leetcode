// 3567. Minimum Absolute Difference in Sliding Submatrix
// Created automatically
// Created at 2026-03-20 11:05:16

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        const int m = static_cast<int>(grid.size());
        const int n = static_cast<int>(grid[0].size());
        const int rows = m - k + 1;
        const int cols = n - k + 1;

        vector<vector<int>> ans(rows, vector<int>(cols, 0));

        struct WindowState {
            map<int, int> freq;
            multiset<int> gaps;

            void addGap(int a, int b) { gaps.insert(b - a); }

            void removeGap(int a, int b) {
                auto it = gaps.find(b - a);
                if (it != gaps.end()) gaps.erase(it);
            }

            void addValue(int x) {
                auto it = freq.find(x);
                if (it != freq.end()) {
                    ++it->second;
                    return;
                }

                auto nextIt = freq.lower_bound(x);
                auto prevIt = (nextIt == freq.begin()) ? freq.end() : prev(nextIt);

                if (prevIt != freq.end() && nextIt != freq.end()) {
                    removeGap(prevIt->first, nextIt->first);
                }
                if (prevIt != freq.end()) addGap(prevIt->first, x);
                if (nextIt != freq.end()) addGap(x, nextIt->first);

                freq.emplace(x, 1);
            }

            void removeValue(int x) {
                auto it = freq.find(x);
                if (it == freq.end()) return;

                if (it->second >= 2) {
                    --it->second;
                    return;
                }

                auto nextIt = next(it);
                auto prevIt = (it == freq.begin()) ? freq.end() : prev(it);

                if (prevIt != freq.end()) removeGap(prevIt->first, x);
                if (nextIt != freq.end()) removeGap(x, nextIt->first);
                if (prevIt != freq.end() && nextIt != freq.end()) {
                    addGap(prevIt->first, nextIt->first);
                }

                freq.erase(it);
            }

            int queryMinAbsDiff() const {
                if (freq.size() <= 1) return 0;
                return *gaps.begin();
            }
        };

        WindowState window;

        // Build initial k x k window at (0, 0).
        for (int r = 0; r < k; ++r) {
            for (int c = 0; c < k; ++c) {
                window.addValue(grid[r][c]);
            }
        }

        int top = 0;
        int left = 0;

        while (true) {
            ans[top][left] = window.queryMinAbsDiff();

            if (top % 2 == 0) {
                // Even row of answers: move from left to right.
                if (left + 1 < cols) {
                    const int removeCol = left;
                    const int addCol = left + k;
                    for (int r = top; r < top + k; ++r) {
                        window.removeValue(grid[r][removeCol]);
                        window.addValue(grid[r][addCol]);
                    }
                    ++left;
                    continue;
                }
            } else {
                // Odd row of answers: move from right to left.
                if (left - 1 >= 0) {
                    const int removeCol = left + k - 1;
                    const int addCol = left - 1;
                    for (int r = top; r < top + k; ++r) {
                        window.removeValue(grid[r][removeCol]);
                        window.addValue(grid[r][addCol]);
                    }
                    --left;
                    continue;
                }
            }

            // Move down one row if possible.
            if (top + 1 >= rows) break;
            const int removeRow = top;
            const int addRow = top + k;
            for (int c = left; c < left + k; ++c) {
                window.removeValue(grid[removeRow][c]);
                window.addValue(grid[addRow][c]);
            }
            ++top;
        }

        return ans;
    }
};
