//
// Created by azote on 12/5/25.
//
#include <vector>
using namespace std;

class Solution {
public:
    int countPartitions(vector<int> &nums) {
        int sum = 0;
        for (const auto element: nums) {
            sum += element;
        }
        if (sum % 2) {
            return 0;
        }
        return nums.size() - 1;
    }
};
