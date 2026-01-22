//
// Created by azote on 1/22/26.
//
#include <vector>
using namespace std;

class Solution {
    static bool isNonDecreasing(const vector<int> &nums, const int start, const int end) {
        for (int i = start; i < end; ++i) {
            if (nums[i] > nums[i + 1]) {
                return false;
            }
        }
        return true;
    }

public:
    int minimumPairRemoval(vector<int> &nums) {
        int len = nums.size();
        int cnt = 0;
        while (!isNonDecreasing(nums, 0, len - 1)) {
            // Find the adjacent pair with minimum sum (leftmost if ties)
            int minPair = 0;
            int minSum = nums[0] + nums[1];
            for (int i = 1; i < len - 1; ++i) {
                const int curSum = nums[i] + nums[i + 1];
                if (curSum < minSum) {
                    minSum = curSum;
                    minPair = i;
                }
            }
            // Replace the pair with their sum
            nums[minPair] = minSum;
            len--;
            cnt++;
            // Shift remaining elements left
            for (int i = minPair + 1; i < len; ++i) {
                nums[i] = nums[i + 1];
            }
        }
        return cnt;
    }
};
