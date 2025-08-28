//
// Created by user on 2025/8/28.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        for (int a = 0; a < nums.size(); ++a) {
            if(a>0 && nums[a]==nums[a-1]){
                continue;
            }
            int target = -nums[a];
            int c = nums.size()-1;
            for (int b = a+1; b < nums.size(); ++b) {
                if(b!=a+1 && nums[b]==nums[b-1]){
                    continue;
                }
                if(b >= c){
                    break;
                }
                if(nums[b]+nums[c]==target){
                    ans.push_back({nums[a], nums[b], nums[c]});
                }
                if(nums[b]+nums[c]<target){
                    continue;
                }
                while(nums[b]+nums[c]>target){
                    c--;
                    if(b==c){
                        break;
                    }
                    if(nums[b]+nums[c]==target){
                        ans.push_back({nums[a], nums[b], nums[c]});
                        break;
                    }
                }
            }
        }
        return ans;
    }
};