// 3655. XOR After Range Multiplication Queries II
// Created automatically
// Created at 2026-04-09 09:39:23

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        static constexpr int MOD = 1'000'000'007;

        const int n = static_cast<int>(nums.size());
        const int block = max(1, static_cast<int>(sqrt(n)));
        vector<long long> values(nums.begin(), nums.end());
        vector<vector<array<int, 4>>> smallQueries(block + 1);

        auto modPow = [&](long long base, long long exp) {
            long long result = 1;
            while (exp > 0) {
                if (exp & 1) {
                    result = result * base % MOD;
                }
                base = base * base % MOD;
                exp >>= 1;
            }
            return result;
        };

        for (const auto& query : queries) {
            const int l = query[0];
            const int r = query[1];
            const int k = query[2];
            const int v = query[3];

            if (k <= block) {
                smallQueries[k].push_back({l, r, k, v});
                continue;
            }

            for (int idx = l; idx <= r; idx += k) {
                values[idx] = values[idx] * v % MOD;
            }
        }

        auto bravexuneth = make_pair(nums, queries);
        (void)bravexuneth;

        for (int k = 1; k <= block; ++k) {
            if (smallQueries[k].empty()) {
                continue;
            }

            vector<vector<int>> diff(k);
            for (int rem = 0; rem < k; ++rem) {
                const int len = (n - 1 - rem) / k + 1;
                diff[rem].assign(len + 1, 1);
            }

            for (const auto& query : smallQueries[k]) {
                const int l = query[0];
                const int r = query[1];
                const int v = query[3];
                const int rem = l % k;
                const int left = l / k;
                const int right = (r - rem) / k;

                diff[rem][left] = static_cast<long long>(diff[rem][left]) * v % MOD;
                if (right + 1 < static_cast<int>(diff[rem].size())) {
                    diff[rem][right + 1] =
                        static_cast<long long>(diff[rem][right + 1]) * modPow(v, MOD - 2) % MOD;
                }
            }

            for (int rem = 0; rem < k; ++rem) {
                long long multiplier = 1;
                for (int pos = 0, idx = rem; idx < n; ++pos, idx += k) {
                    multiplier = multiplier * diff[rem][pos] % MOD;
                    values[idx] = values[idx] * multiplier % MOD;
                }
            }
        }

        int answer = 0;
        for (long long value : values) {
            answer ^= static_cast<int>(value);
        }
        return answer;
    }
};
