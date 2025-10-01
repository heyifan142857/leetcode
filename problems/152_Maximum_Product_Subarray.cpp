//
// Created by user on 2025/10/1.
//
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = nums[0];
        int n = nums.size();
        vector<int> _nums = nums;
        for (int i = 1; i < n; ++i) {
            int cur = nums[i];
            nums[i] = max(nums[i], nums[i]*nums[i-1]);
            nums[i] = max(nums[i], _nums[i-1]*cur);
            _nums[i] = min(_nums[i], _nums[i]*_nums[i-1]);
            _nums[i] = min(_nums[i], nums[i-1]*cur);
            ans = max(ans, nums[i]);
        }
        return ans;
    }
};