//
// Created by user on 2025/9/1.
//

#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        for (auto& num: nums) {
            if(num <= 0){
                num = n+1;
            }
        }

        for (int i = 0; i < n; ++i) {
            int cur = abs(nums[i]);
            if(cur <= n){
                nums[cur-1] = -abs(nums[cur-1]);
            }
        }
        int i = 0;
        for (; i < n; ++i) {
            if(nums[i]>0){
                break;
            }
        }
        return i+1;
    }
};