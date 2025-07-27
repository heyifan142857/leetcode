//
// Created by user on 2025/7/27.
//
#include <vector>
using namespace std;

class Solution {
public:
    int countHillValley(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2){
            return 0;
        }

        int count = 0;
        int now = nums[0], before = nums[0];

        for (int i = 0; i < n; ++i) {
            if(now != nums[i]){
                if((nums[i]-now)*(now-before)<0){
                    count++;
                }
                before = now;
                now = nums[i];

            }
        }
        return count;
    }
};