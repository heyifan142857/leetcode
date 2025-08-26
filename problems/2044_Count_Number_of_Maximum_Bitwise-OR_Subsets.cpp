//
// Created by user on 2025/7/28.
//
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int max_or = 0;
        for (int num : nums) {
            max_or |= num;
        }

        int n = nums.size();
        int count = 0;

        //子集的表示：位掩码（Bitmask）
        for (int mask = 1; mask < (1 << n); ++mask) {
            int current_or = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    current_or |= nums[i];
                }
            }
            if (current_or == max_or) {
                ++count;
            }
        }

        return count;
    }
};