//
// Created by user on 2025/7/29.
//

#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        map<int, int> or_values;

        vector<int> ans(n, 0);

        for (int i = n-1; i >= 0; --i) {
            map<int, int> new_or_values;
            new_or_values.insert(make_pair(nums[i], i));

            for (const auto pair: or_values) {
                int new_or = pair.first | nums[i];
                if(new_or_values.find(new_or) == new_or_values.end()){
                    new_or_values[new_or] = pair.second;
                }
            }

            auto max_or_value = *new_or_values.rbegin();
            ans[i] = max_or_value.second - i +1;

            or_values = new_or_values;
        }

        return ans;
    }
};
