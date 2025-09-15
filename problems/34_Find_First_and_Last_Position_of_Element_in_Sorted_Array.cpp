//
// Created by user on 2025/9/15.
//
#include <vector>
using namespace std;

class Solution {
    vector<int> ans = {-1, -1};

    int searchLeft(vector<int>& nums, int l, int r, int target){
        if(l > r){
            return -1;
        }
        if(l==r){
            return l;
        }
        int mid = (l+r)/2;
        if(nums[mid] < target){
            return searchLeft(nums, mid+1, r, target);
        }else{
            if(mid == 0 || nums[mid-1] < target){
                return mid;
            }
            return searchLeft(nums, l, mid-1, target);
        }
    }

    int searchRight(vector<int>& nums, int l, int r, int target){
        if(l > r){
            return -1;
        }
        if(l==r){
            return l;
        }
        int mid = (l+r)/2;
        if(nums[mid] > target){
            return searchRight(nums, l, mid-1, target);
        }else{
            if(mid == nums.size()-1 || nums[mid+1] > target){
                return mid;
            }
            return searchRight(nums, mid+1, r, target);
        }
    }

    void _searchRange(vector<int>& nums, int l, int r, int target){
        if(l > r){
            return;
        }
        int mid = (l+r)/2;
        if(nums[mid] == target){
            ans[0] = searchLeft(nums, l, mid, target);
            ans[1] = searchRight(nums, mid, r, target);
        }else if(nums[mid] > target){
            _searchRange(nums, l, mid-1, target);
        }else{
            _searchRange(nums, mid+1, r, target);
        }
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        _searchRange(nums, 0, nums.size()-1, target);

        return ans;
    }
};
