// Weekly Contest 496 - Q3
// Created automatically
// Created at 2026-04-05 17:31:25

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minIncrease(vector<int>& nums) {
        const int n = static_cast<int>(nums.size());
        if (n <= 2) return 0;

        auto peakCost = [&](int i) -> long long {
            long long need = max(nums[i - 1], nums[i + 1]) + 1LL - nums[i];
            return max(0LL, need);
        };

        struct State {
            int peaks;
            long long cost;
        };

        auto better = [](const State& a, const State& b) -> State {
            if (a.peaks != b.peaks) return a.peaks > b.peaks ? a : b;
            return a.cost < b.cost ? a : b;
        };

        const int NEG_INF = numeric_limits<int>::min() / 4;
        const long long INF = (1LL << 62);

        State skip{0, 0};
        State take{NEG_INF, INF};

        for (int i = 1; i <= n - 2; ++i) {
            State nextSkip = better(skip, take);
            State nextTake{NEG_INF, INF};
            if (skip.peaks > NEG_INF / 2) {
                nextTake = {skip.peaks + 1, skip.cost + peakCost(i)};
            }
            skip = nextSkip;
            take = nextTake;
        }

        return better(skip, take).cost;
    }
};
