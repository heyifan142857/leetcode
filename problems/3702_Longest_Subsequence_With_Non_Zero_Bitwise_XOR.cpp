// 3702. Longest Subsequence With Non-Zero Bitwise XOR

#include <vector>
using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int> &nums) {
        const int n = static_cast<int>(nums.size());
        int xorSum = 0;
        bool hasNonZero = false;

        for (int num : nums) {
            xorSum ^= num;
            hasNonZero |= num != 0;
        }

        if (!hasNonZero) {
            return 0;
        }

        return xorSum != 0 ? n : n - 1;
    }
};
