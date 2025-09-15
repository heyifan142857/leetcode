//
// Created by user on 2025/9/15.
//
#include <vector>
using namespace std;

class Solution {
    int _searchInsert(vector<int>& nums, int l, int r, int target){
        int mid = (l + r) / 2;
        if(l > r){
            return l;
        }
        if(nums[mid] == target){
            return mid;
        }
        if(nums[mid] > target){
            return _searchInsert(nums, l, mid-1, target);
        }else{
            return _searchInsert(nums, mid+1, r, target);
        }
    }
public:
    int searchInsert(vector<int>& nums, int target) {
        return _searchInsert(nums, 0, nums.size()-1, target);
    }
};