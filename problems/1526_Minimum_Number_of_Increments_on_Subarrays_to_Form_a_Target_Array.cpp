//
// Created by user on 2025/10/30.
//
#include <vector>

using namespace std;

class Solution {
public:
    int minNumberOperations(vector<int> &target) {
        int n = target.size();
        int ans = target[0];
        for (int i = 1; i < n; ++i) {
            ans += max(target[i] - target[i - 1], 0);
        }
        return ans;
    }
};
