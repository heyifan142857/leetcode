//
// Created by user on 2025/8/31.
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> begin(n, 1);
        vector<int> end(n, 1);
        for (int i = 1; i < n; ++i) {
            begin[i] = nums[i-1] * begin[i-1];
            end[n-1-i] = nums[n-i] * end[n-i];
        }
        vector<int> ans(n, 1);
        for (int i = 0; i < n; ++i) {
            ans[i] = begin[i]*end[i];
        }
        return ans;
    }
};