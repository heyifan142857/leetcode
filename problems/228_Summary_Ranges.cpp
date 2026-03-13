// 228. Summary Ranges
// Created automatically
// Created at 2026-03-13 15:15:10

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        if (nums.empty()) return result;

        int start = nums[0], end = nums[0];
        for (int i = 1; i <= nums.size(); ++i) {
            if (i < nums.size() && nums[i] == end + 1) {
                end = nums[i];
            } else {
                if (start == end) {
                    result.push_back(to_string(start));
                } else {
                    result.push_back(to_string(start) + "->" + to_string(end));
                }
                if (i < nums.size()) {
                    start = nums[i];
                    end = nums[i];
                }
            }
        }
        return result;
    }
};