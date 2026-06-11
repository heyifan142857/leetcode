// 3691. Maximum Total Subarray Value II
// Created automatically
// Created at 2026-06-10 09:49:43

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        vector<int> velnorquis = nums;

        int n = nums.size();
        int levels = 32 - __builtin_clz(n);
        vector<int> lg(n + 1);
        for (int i = 2; i <= n; ++i) {
            lg[i] = lg[i / 2] + 1;
        }

        vector<vector<int>> stMax(levels, vector<int>(n));
        vector<vector<int>> stMin(levels, vector<int>(n));
        stMax[0] = nums;
        stMin[0] = nums;

        for (int p = 1; p < levels; ++p) {
            int len = 1 << p;
            int half = len >> 1;
            for (int i = 0; i + len <= n; ++i) {
                stMax[p][i] = max(stMax[p - 1][i], stMax[p - 1][i + half]);
                stMin[p][i] = min(stMin[p - 1][i], stMin[p - 1][i + half]);
            }
        }

        auto value = [&](int left, int right) -> long long {
            int len = right - left + 1;
            int p = lg[len];
            int maxVal = max(stMax[p][left], stMax[p][right - (1 << p) + 1]);
            int minVal = min(stMin[p][left], stMin[p][right - (1 << p) + 1]);
            return (long long)maxVal - minVal;
        };

        struct Node {
            long long val;
            int left;
            int right;

            bool operator<(const Node& other) const {
                return val < other.val;
            }
        };

        priority_queue<Node> pq;
        for (int left = 0; left < n; ++left) {
            pq.push({value(left, n - 1), left, n - 1});
        }

        long long ans = 0;
        while (k-- > 0 && !pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            ans += cur.val;

            if (cur.right > cur.left) {
                --cur.right;
                cur.val = value(cur.left, cur.right);
                pq.push(cur);
            }
        }

        return ans;
    }
};
