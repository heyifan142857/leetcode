//
// Created by user on 2025/8/25.
//

#include <vector>
using namespace std;

class Solution {
public:
    int countPairs(vector<int>& nums, int k) {
        int total = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i+1; j < nums.size(); ++j) {
                if(nums[i] == nums[j] && (i*j)%k == 0){
                    total++;
                }
            }
        }
        return total;
    }
};