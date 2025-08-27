//
// Created by user on 2025/8/27.
//

#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set set(nums.begin(), nums.end());

        int max_len = 0;

        for (auto n: nums) {
            if(!set.count(n-1)){
                int cur_len = 0;
                while (set.count(n)){
                    cur_len++;
                    n++;
                }
                max_len = max(max_len, cur_len);
            }
        }
        return max_len;
    }
};