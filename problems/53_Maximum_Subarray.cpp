//
// Created by user on 2025/8/30.
//

#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> dp = vector(nums.size(), 0);
        int cur = INT_MIN;
        int ans = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            cur = max(cur+nums[i], nums[i]);
            ans = max(ans, cur);
        }
        return ans;
    }
};