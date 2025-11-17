//
// Created by azote on 11/17/25.
//
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    bool kLengthApart(vector<int> &nums, int k) {
        int cur = INT_MAX;
        for (auto i: nums) {
            if (i == 1) {
                if (cur < k) {
                    return false;
                }
                cur = 0;
            } else {
                if (cur < INT_MAX) {
                    cur++;
                }
            }
        }
        return true;
    }
};
