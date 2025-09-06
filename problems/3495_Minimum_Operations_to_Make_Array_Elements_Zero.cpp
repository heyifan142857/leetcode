//
// Created by user on 2025/9/6.
//

#include <vector>
using namespace std;

class Solution {
    long long makeZeroCount(int l, int r) {
        auto steps = [](int x) {
            int cnt = 0;
            while (x > 0) {
                x /= 4;
                cnt++;
            }
            return cnt;
        };

        int opL = steps(l);
        int opR = steps(r);
        long long totalSteps = 0;
        int prev = l;

        long long start = 1;
        for (int k = 1; k <= opR; k++) {
            long long low = max((long long)prev, start);
            long long high = min((long long)r, start * 4 - 1);
            if (low <= high) {
                totalSteps += (high - low + 1) * 1LL * k;
                prev = high + 1;
            }
            start *= 4;
        }

        return (totalSteps + 1) / 2;
    }

public:
    long long minOperations(vector<vector<int>>& queries) {
        long long ans = 0;
        for (auto &q : queries) {
            ans += makeZeroCount(q[0], q[1]);
        }
        return ans;
    }
};

