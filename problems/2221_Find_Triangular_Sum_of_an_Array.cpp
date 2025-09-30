//
// Created by user on 2025/9/30.
//
#include <vector>
using namespace std;

class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        if(n == 1){
            return nums[0];
        }
        for (int i = 0; i < n-1; ++i) {
            nums[i] += nums[i+1];
            nums[i] %= 10;
        }
        nums.pop_back();
        return triangularSum(nums);
    }
};