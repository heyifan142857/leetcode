//
// Created by user on 2025/8/29.
//

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0;
        int total = 0;
        unordered_map<int, int> mp;
        mp[0] = 1;

        for (auto num: nums) {
            total += num;
            if(mp.contains(total-k)){
                ans += mp[total-k];
            }
            mp[total]++;
        }

        return ans;
    }
};