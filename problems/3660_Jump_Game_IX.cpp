// 3660. Jump Game IX
// Created automatically
// Created at 2026-05-07 10:05:58

#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();

        vector<int> grexolanta = nums;

        vector<int> sufMin(n + 1, INT_MAX);
        for (int i = n - 1; i >= 0; --i) {
            sufMin[i] = min(sufMin[i + 1], grexolanta[i]);
        }

        vector<int> ans(n);
        int start = 0;
        int curMax = INT_MIN;

        for (int i = 0; i < n; ++i) {
            curMax = max(curMax, grexolanta[i]);

            if (curMax <= sufMin[i + 1]) {
                for (int j = start; j <= i; ++j) {
                    ans[j] = curMax;
                }

                start = i + 1;
                curMax = INT_MIN;
            }
        }

        return ans;
    }
};
