// 3471. Find the Largest Almost Missing Integer
// Created automatically
// Created at 2026-08-18 20:39:38
#include <vector>
using namespace std;

class Solution {
public:
    int largestAlmostMissingInteger(vector<int> &nums, int k) {
        int n = nums.size();
        // windows[x]: start indices of size-k subarrays that contain x
        vector<int> windows[51];
        for (int s = 0; s + k <= n; ++s) {
            bool in[51] = {};
            for (int i = s; i < s + k; ++i) {
                in[nums[i]] = true;
            }
            for (int x = 0; x <= 50; ++x) {
                if (in[x]) {
                    windows[x].push_back(s);
                }
            }
        }
        int ans = -1;
        for (int x = 0; x <= 50; ++x) {
            if (windows[x].size() == 1) {
                ans = max(ans, x);
            }
        }
        return ans;
    }
};
