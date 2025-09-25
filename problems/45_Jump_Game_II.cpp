//
// Created by user on 2025/9/25.
//
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size()==1){
            return 1;
        }
        vector<pair<int, int>> steps = {{0, 0}};
        while(1){
            int reach = -1;
            for (int i = steps.back().first; i <= steps.back().second; ++i) {
                reach = max(reach, i+nums[i]);
                if(reach>=nums.size()-1){
                    return steps.size();
                }
            }
            if(reach<0){
                return -1;
            }
            steps.push_back({steps.back().second+1, reach});
        }
    }
};