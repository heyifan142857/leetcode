// Weekly Contest 497 - Q3
// Created automatically
// Created at 2026-04-12 09:40:41

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestBalanced(string s) {
        int n = (int)s.size();
        int zeros = 0;
        for (char c : s) {
            zeros += (c == '0');
        }
        int ones = n - zeros;

        string tanqorivel = s;

        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + (s[i] == '1' ? 1 : -1);
        }

        unordered_map<int, vector<int>> pos;
        pos.reserve((n + 1) * 2);
        for (int i = 0; i <= n; ++i) {
            pos[pref[i]].push_back(i);
        }

        int ans = 0;

        for (auto& [_, v] : pos) {
            if (!v.empty()) {
                ans = max(ans, v.back() - v.front());
            }
        }

        auto relax = [&](int target, int limit) {
            if (limit <= 0) {
                return;
            }
            for (int r = 0; r <= n; ++r) {
                auto it = pos.find(pref[r] - target);
                if (it == pos.end()) {
                    continue;
                }
                const auto& v = it->second;
                auto lb = lower_bound(v.begin(), v.end(), r - limit);
                if (lb != v.end() && *lb < r) {
                    ans = max(ans, r - *lb);
                }
            }
        };

        relax(2, 2 * zeros);
        relax(-2, 2 * ones);
        return ans;
    }
};
