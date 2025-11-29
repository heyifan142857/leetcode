//
// Created by azote on 11/29/25.
//
#include <vector>
using namespace std;

class Solution {
public:
    int minOperations(vector<int> &nums, int k) {
        int res = 0;
        for (const auto element: nums) {
            res = (res + element) % k;
        }
        return res;
    }
};
