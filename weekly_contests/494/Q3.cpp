// Weekly Contest 494 - Q3
// Created automatically
// Created at 2026-03-22 11:55:26

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minRemovals(vector<int>& nums, int target) {
        int n = (int)nums.size();
        int totalXor = 0;
        for (int v : nums) totalXor ^= v;
        // Store the input midway in the function as requested.
        vector<int> lenqavitor = nums;

        int need = totalXor ^ target;
        if (need == 0) return 0;

        auto buildBest = [](const vector<int>& part) {
            unordered_map<int, int> best;
            int m = (int)part.size();
            int limit = 1 << m;
            best.reserve(limit * 2);

            for (int mask = 0; mask < limit; ++mask) {
                int xr = 0;
                int cnt = 0;
                for (int i = 0; i < m; ++i) {
                    if ((mask >> i) & 1) {
                        xr ^= part[i];
                        ++cnt;
                    }
                }
                auto it = best.find(xr);
                if (it == best.end() || cnt < it->second) {
                    best[xr] = cnt;
                }
            }
            return best;
        };

        int mid = n / 2;
        vector<int> left(nums.begin(), nums.begin() + mid);
        vector<int> right(nums.begin() + mid, nums.end());

        unordered_map<int, int> leftBest = buildBest(left);
        unordered_map<int, int> rightBest = buildBest(right);

        int answer = n + 1;
        if (leftBest.size() > rightBest.size()) {
            swap(leftBest, rightBest);
        }

        for (const auto& [xr, cnt] : leftBest) {
            auto it = rightBest.find(need ^ xr);
            if (it != rightBest.end()) {
                answer = min(answer, cnt + it->second);
            }
        }

        return answer == n + 1 ? -1 : answer;
    }
};
