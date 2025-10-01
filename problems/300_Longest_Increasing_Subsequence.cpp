//
// Created by user on 2025/10/1.
//
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1, 1);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if(nums[j-1] < nums[i-1]){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
