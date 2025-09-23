//
// Created by user on 2025/9/23.
//
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if(i>maxReach){
                return false;
            }
            maxReach = max(maxReach, i+nums[i]);
            if(maxReach>=nums.size()-1){
                return true;
            }
        }
        return true;
    }
};