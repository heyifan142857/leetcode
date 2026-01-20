//
// Created by azote on 1/20/26.
//
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> minBitwiseArray(vector<int> &nums) {
        const int n = nums.size();
        vector<int> ans;
        for (const auto num: nums) {
            const int start = num >> 1;
            const int end = num;
            bool flag = false;
            for (int i = start; i <= end; ++i) {
                if ((i | (i + 1)) == num) {
                    ans.push_back(i);
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                ans.push_back(-1);
            }
        }
        return ans;
    }
};
