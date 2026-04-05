// Weekly Contest 496 - Q4
// Created automatically
// Created at 2026-04-05 17:31:25

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());
        if (k == 0) return 0;
        if (n == 1) return -1;
        if (k > n / 2) return -1;

        vector<long long> cost(n, 0);
        for (int i = 0; i < n; ++i) {
            int left = nums[(i - 1 + n) % n];
            int right = nums[(i + 1) % n];
            long long need = max(left, right) + 1LL - nums[i];
            cost[i] = max(0LL, need);
        }

        const long long INF = (1LL << 62);

        auto solvePath = [&](int left, int right, int need) -> long long {
            if (need == 0) return 0;
            if (left > right) return INF;

            int len = right - left + 1;
            if (need > (len + 1) / 2) return INF;

            vector<long long> skip(need + 1, INF), take(need + 1, INF);
            skip[0] = 0;

            for (int i = left; i <= right; ++i) {
                for (int used = need; used >= 0; --used) {
                    long long oldSkip = skip[used];
                    long long oldTake = take[used];

                    take[used] = INF;
                    if (used > 0 && skip[used - 1] != INF) {
                        take[used] = skip[used - 1] + cost[i];
                    }

                    skip[used] = min(oldSkip, oldTake);
                }
            }

            return min(skip[need], take[need]);
        };

        long long answer = solvePath(1, n - 1, k);
        if (k >= 1) {
            long long withFirst = solvePath(2, n - 2, k - 1);
            if (withFirst != INF) {
                answer = min(answer, withFirst + cost[0]);
            }
        }

        return answer == INF ? -1 : static_cast<int>(answer);
    }
};
