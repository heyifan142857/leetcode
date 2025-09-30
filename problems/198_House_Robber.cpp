//
// Created by user on 2025/9/30.
//
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            if(i==0){
                continue;
            }

            if(i==1){
                nums[i] = max(nums[i-1], nums[i]);
                continue;
            }

            nums[i] = max(nums[i-1], nums[i-2]+nums[i]);
        }

        return nums[n-1];
    }
};