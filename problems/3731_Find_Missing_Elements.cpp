// 3731. Find Missing Elements
// Created automatically
// Created at 2026-08-04 17:59:10

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int start = *min_element(nums.begin(), nums.end());
        int end = *max_element(nums.begin(), nums.end());
        unordered_set<int> seen(nums.begin(), nums.end());
        vector<int> missing;
        for (int i = start; i <= end; ++i) {
            if (seen.find(i) == seen.end()) {
                missing.push_back(i);
            }
        }
        return missing;
    }
};