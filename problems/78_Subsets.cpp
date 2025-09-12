//
// Created by user on 2025/9/12.
//
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> ans;
    void _subsets(vector<int>& nums, vector<int>& subset, int p) {
        if(p >= nums.size()){
            ans.push_back(subset);
            return;
        }
        _subsets(nums, subset, p+1);
        subset.push_back(nums[p]);
        _subsets(nums, subset, p+1);
        subset.pop_back();
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> subset;
        _subsets(nums, subset, 0);
        return ans;
    }
};