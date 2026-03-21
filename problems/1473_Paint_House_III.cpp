// 1473. Paint House III
// Created automatically
// Created at 2026-03-21 20:09:45

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        const int INF = 1e9;
        vector<vector<int>> prev(target + 1, vector<int>(n + 1, INF));
        vector<vector<int>> curr(target + 1, vector<int>(n + 1, INF));

        if (houses[0] != 0) {
            prev[1][houses[0]] = 0;
        } else {
            for (int color = 1; color <= n; ++color) {
                prev[1][color] = cost[0][color - 1];
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int groups = 0; groups <= target; ++groups) {
                fill(curr[groups].begin(), curr[groups].end(), INF);
            }

            for (int groups = 1; groups <= min(target, i + 1); ++groups) {
                for (int prevColor = 1; prevColor <= n; ++prevColor) {
                    if (prev[groups][prevColor] == INF) {
                        continue;
                    }

                    if (houses[i] != 0) {
                        int color = houses[i];
                        int nextGroups = groups + (color != prevColor);
                        if (nextGroups <= target) {
                            curr[nextGroups][color] =
                                min(curr[nextGroups][color], prev[groups][prevColor]);
                        }
                    } else {
                        for (int color = 1; color <= n; ++color) {
                            int nextGroups = groups + (color != prevColor);
                            if (nextGroups > target) {
                                continue;
                            }
                            curr[nextGroups][color] = min(
                                curr[nextGroups][color],
                                prev[groups][prevColor] + cost[i][color - 1]
                            );
                        }
                    }
                }
            }

            swap(prev, curr);
        }

        int answer = INF;
        for (int color = 1; color <= n; ++color) {
            answer = min(answer, prev[target][color]);
        }

        return answer == INF ? -1 : answer;
    }
};
