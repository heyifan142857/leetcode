// 3488. Closest Equal Element Queries
// Created automatically
// Created at 2026-04-16 10:18:52

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        const int n = static_cast<int>(nums.size());
        unordered_map<int, vector<int>> positions;
        positions.reserve(n * 2);

        for (int i = 0; i < n; ++i) {
            positions[nums[i]].push_back(i);
        }

        vector<int> best(n, -1);

        for (auto& [value, idxs] : positions) {
            const int m = static_cast<int>(idxs.size());
            if (m == 1) {
                continue;
            }

            for (int i = 0; i < m; ++i) {
                const int cur = idxs[i];
                const int prev = idxs[(i - 1 + m) % m];
                const int next = idxs[(i + 1) % m];

                const int distPrev = min(abs(cur - prev), n - abs(cur - prev));
                const int distNext = min(abs(next - cur), n - abs(next - cur));
                best[cur] = min(distPrev, distNext);
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());
        for (int q : queries) {
            answer.push_back(best[q]);
        }
        return answer;
    }
};
