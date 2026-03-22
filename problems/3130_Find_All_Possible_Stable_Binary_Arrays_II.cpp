// 3130. Find All Possible Stable Binary Arrays II
// Created automatically
// Created at 2026-03-22 12:12:36

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        static constexpr int MOD = 1'000'000'007;

        if (zero == 0 && one == 0) {
            return 1;
        }

        vector<vector<int>> endWithZero(zero + 1, vector<int>(one + 1, 0));
        vector<vector<int>> endWithOne(zero + 1, vector<int>(one + 1, 0));

        // Prefix sums for fast range queries in the transitions:
        // rowZero[i][j] = sum(endWithZero[i][0..j])
        // colOne[j][i] = sum(endWithOne[0..i][j])
        vector<vector<int>> rowZero(zero + 1, vector<int>(one + 1, 0));
        vector<vector<int>> colOne(one + 1, vector<int>(zero + 1, 0));

        for (int i = 0; i <= zero; ++i) {
            for (int j = 0; j <= one; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }

                if (i > 0) {
                    if (j == 0) {
                        endWithZero[i][j] = (i <= limit);
                    } else {
                        int left = max(0, i - limit);
                        long long ways = colOne[j][i - 1];
                        if (left > 0) {
                            ways -= colOne[j][left - 1];
                        }
                        endWithZero[i][j] = (ways % MOD + MOD) % MOD;
                    }
                }

                if (j > 0) {
                    if (i == 0) {
                        endWithOne[i][j] = (j <= limit);
                    } else {
                        int left = max(0, j - limit);
                        long long ways = rowZero[i][j - 1];
                        if (left > 0) {
                            ways -= rowZero[i][left - 1];
                        }
                        endWithOne[i][j] = (ways % MOD + MOD) % MOD;
                    }
                }

                rowZero[i][j] = endWithZero[i][j];
                if (j > 0) {
                    rowZero[i][j] += rowZero[i][j - 1];
                    if (rowZero[i][j] >= MOD) {
                        rowZero[i][j] -= MOD;
                    }
                }

                colOne[j][i] = endWithOne[i][j];
                if (i > 0) {
                    colOne[j][i] += colOne[j][i - 1];
                    if (colOne[j][i] >= MOD) {
                        colOne[j][i] -= MOD;
                    }
                }
            }
        }

        int answer = endWithZero[zero][one] + endWithOne[zero][one];
        if (answer >= MOD) {
            answer -= MOD;
        }
        return answer;
    }
};
