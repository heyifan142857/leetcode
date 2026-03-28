// 2573. Find the String with LCP
// Created automatically
// Created at 2026-03-28 00:56:45

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        if (n == 0) return "";
        for (int i = 0; i < n; ++i) if ((int)lcp[i].size() != n) return "";

        // Basic validity checks.
        for (int i = 0; i < n; ++i) {
            if (lcp[i][i] != n - i) return "";
            for (int j = 0; j < n; ++j) {
                if (lcp[i][j] < 0 || lcp[i][j] > n - max(i, j)) return "";
                if (lcp[i][j] != lcp[j][i]) return "";
            }
        }

        // Greedily build the lexicographically smallest candidate.
        string s(n, '?');
        char cur = 'a';
        for (int i = 0; i < n; ++i) {
            if (s[i] != '?') continue;
            if (cur > 'z') return "";
            s[i] = cur;
            for (int j = i + 1; j < n; ++j) {
                if (lcp[i][j] > 0) s[j] = cur;
            }
            ++cur;
        }

        // Verify by recomputing full lcp with O(n^2) DP.
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (s[i] == s[j]) dp[i][j] = 1 + dp[i + 1][j + 1];
                if (dp[i][j] != lcp[i][j]) return "";
            }
        }

        return s;
    }
};
