//
// Created by user on 2025/9/15.
//
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    int _findMin(vector<int>& nums, int l, int r) {
        int mid = (l+r)/2;
        if(l == mid){
            return min(nums[l], nums[r]);
        }
        if(nums[mid] > nums[l] && nums[r] < nums[l]){
            return _findMin(nums, mid+1, r);
        }else{
            if(mid == 0 || nums[mid-1] > nums[mid]){
                return nums[mid];
            }
            return _findMin(nums, l, mid-1);
        }
    }
public:
    int findMin(vector<int>& nums) {
        return _findMin(nums, 0, nums.size()-1);
    }
};