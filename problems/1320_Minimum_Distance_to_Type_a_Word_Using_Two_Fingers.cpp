// 1320. Minimum Distance to Type a Word Using Two Fingers
// Created automatically
// Created at 2026-04-12 09:41:00

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDistance(string word) {
        int n = word.size();
        if (n <= 1) return 0;

        const int NONE = 26;
        const int L = 27;

        vector<int> memo(n * L * L, -1);

        auto cost = [&](int a, int b) {
            return abs(a / 6 - b / 6) + abs(a % 6 - b % 6);
        };

        function<int(int,int,int)> dfs = [&](int i, int f1, int f2) -> int {
            if (i == n) return 0;
            int idx = i * L * L + f1 * L + f2;
            if (memo[idx] != -1) return memo[idx];
            int t = word[i] - 'A';

            int use1 = (f1 == NONE ? 0 : cost(f1, t)) + dfs(i + 1, t, f2);
            int use2 = (f2 == NONE ? 0 : cost(f2, t)) + dfs(i + 1, f1, t);

            memo[idx] = min(use1, use2);
            return memo[idx];
        };

        return dfs(0, NONE, NONE);
    }
};