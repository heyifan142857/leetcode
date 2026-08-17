// 2958. Length of Longest Subarray With at Most K Frequency
// Created automatically
// Created at 2026-08-12 19:12:47

#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int> &nums, int k) {
        unordered_map<int, int> freq;
        int left = 0;
        int ans = 0;

        for (int right = 0; right < nums.size(); ++right) {
            ++freq[nums[right]];

            while (freq[nums[right]] > k) {
                --freq[nums[left]];
                ++left;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
