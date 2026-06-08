// 2161. Partition Array According to Given Pivot
// Created automatically
// Created at 2026-06-08 16:05:36

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> result;
        for (int num : nums) {
            if (num < pivot) {
                result.push_back(num);
            }
        }
        for (int num : nums) {
            if (num == pivot) {
                result.push_back(num);
            }
        }
        for (int num : nums) {
            if (num > pivot) {
                result.push_back(num);
            }
        }
        return result;
    }
};