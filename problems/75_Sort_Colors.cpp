//
// Created by user on 2025/10/1.
//
#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = -1;
        int r = nums.size();

        int i = 0;
        while (i < r) {
            int cur = nums[i];
            if(cur==0){
                swap(nums[l+1], nums[i]);
                l++;
            }else if(cur==2){
                swap(nums[r-1], nums[i]);
                r--;
                continue;
            }
            i++;
        }
    }
};