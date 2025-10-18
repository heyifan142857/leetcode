//
// Created by user on 2025/10/18.
//
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        unordered_set<int> set;

        sort(nums.begin(), nums.end());

        int prev = INT_MIN;
        for(auto n: nums){
            if(prev<n+k){
                set.insert(max(prev+1, n-k));
                prev = max(prev+1, n-k);
            }
        }

        return set.size();
    }
};