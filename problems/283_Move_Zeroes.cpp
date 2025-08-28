//
// Created by user on 2025/8/28.
//

#include <vector>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int fast = 0, slow = 0;
        while (fast < nums.size()){
            if(nums[fast]!=0){
                swap(nums[fast], nums[slow]);
                slow++;
            }

            fast++;
        }
    }
};