//
// Created by user on 2025/10/2.
//
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        bool changed = false;
        for (int i = nums.size()-1; i > 0; --i) {
            if(nums[i]>nums[i-1]){
                int swap_flag = i;
                for (; swap_flag < nums.size()-1; ++swap_flag) {
                    if(nums[swap_flag+1]<=nums[i-1]){
                        break;
                    }
                }
                swap(nums[i-1], nums[swap_flag]);
                sort(nums.begin()+i, nums.end());
                changed = true;
                break;
            }
        }
        if(!changed){
            sort(nums.begin(), nums.end());
        }
    }
};