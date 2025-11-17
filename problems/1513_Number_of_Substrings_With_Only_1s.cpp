//
// Created by azote on 11/17/25.
//
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int numSub(string s) {
        vector<long long> lengths;
        int cur = 0;
        for (const auto c: s) {
            if (c == '0') {
                if (cur) {
                    lengths.push_back(cur);
                }
                cur = 0;
            } else {
                cur++;
            }
        }
        if (cur) {
            lengths.push_back(cur);
        }

        ranges::sort(lengths);

        if (lengths.empty()) {
            return 0;
        }

        const int max_len = lengths.back();

        vector<long long> dp(max_len + 1, 0);

        for (int i = 1; i <= max_len; ++i) {
            dp[i] = dp[i - 1] + i;
        }

        long long sum = 0;

        for (const auto length: lengths) {
            sum += dp[length];
        }

        return static_cast<int>(sum % 1000000007);
    }
};
