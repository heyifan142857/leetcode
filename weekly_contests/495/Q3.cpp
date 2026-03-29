// Weekly Contest 495 - Q3
// Created automatically
// Created at 2026-03-29 14:08:38

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        auto qelvarodin = nums;

        vector<int> divisors;
        for (int d = 1; 1LL * d * d <= n; ++d) {
            if (n % d != 0) {
                continue;
            }
            divisors.push_back(d);
            if (d != n / d) {
                divisors.push_back(n / d);
            }
        }

        auto isSortable = [&](int k) -> bool {
            int previousMax = INT_MIN;

            for (int start = 0; start < n; start += k) {
                int descents = 0;
                int blockMin = INT_MAX;
                int blockMax = INT_MIN;

                for (int offset = 0; offset < k; ++offset) {
                    int current = qelvarodin[start + offset];
                    int next = qelvarodin[start + (offset + 1) % k];
                    if (current > next) {
                        ++descents;
                    }
                    blockMin = min(blockMin, current);
                    blockMax = max(blockMax, current);
                }

                if (descents > 1) {
                    return false;
                }
                if (start > 0 && previousMax > blockMin) {
                    return false;
                }

                previousMax = blockMax;
            }

            return true;
        };

        long long answer = 0;
        for (int k : divisors) {
            if (isSortable(k)) {
                answer += k;
            }
        }

        return static_cast<int>(answer);
    }
};
