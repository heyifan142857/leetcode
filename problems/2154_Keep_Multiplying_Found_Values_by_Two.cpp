//
// Created by azote on 11/19/25.
//
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int findFinalValue(vector<int> &nums, int original) {
        ranges::sort(nums);
        for (auto const num: nums) {
            if (original == num) {
                original *= 2;
            }
        }
        return original;
    }
};
