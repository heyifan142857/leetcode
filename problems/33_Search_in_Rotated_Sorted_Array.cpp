//
// Created by user on 2025/9/15.
//
#include <vector>
using namespace std;

class Solution {
    int _search_helper(vector<int>& nums, int l, int r, int target){
        if(l>r){
            return -1;
        }
        int mid = (l+r)/2;
        if(nums[mid] == target){
            return mid;
        }
        if(nums[mid] > target){
            return _search_helper(nums, l, mid-1, target);
        }else{
            return _search_helper(nums, mid+1, r, target);
        }
    }
    int _search(vector<int>& nums, int l, int r, int target) {
        if(l > r){
            return -1;
        }
        int mid = (l+r)/2;
        if(nums[mid] == target){
            return mid;
        }
        if(nums[l] == target){
            return l;
        }
        if(nums[r] == target){
            return r;
        }
        if(nums[mid] > nums[l]){
            if(target < nums[mid] && target > nums[l]){
                return _search_helper(nums, l, mid-1, target);
            }else{
                return _search(nums, mid+1, r, target);
            }
        }else{
            if(target > nums[mid] && target < nums[r]){
                return _search_helper(nums, mid+1, r, target);
            }else{
                return _search(nums, l, mid-1, target);
            }
        }
    }
public:
    int search(vector<int>& nums, int target) {
        return _search(nums, 0, nums.size()-1, target);
    }
};