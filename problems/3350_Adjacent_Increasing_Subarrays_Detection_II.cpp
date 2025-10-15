//
// Created by user on 2025/10/15.
//
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int former = INT_MAX;

        vector<int> lengths;
        int len = 0;
        for (auto n: nums) {
            if(n > former){
                len++;
            }else{
                if(len){
                    lengths.push_back(len);
                }
                len = 1;
            }
            former = n;
        }
        lengths.push_back(len);

        int ans = 0;
        for (int i = 0; i < (int)lengths.size(); ++i) {
            ans = max(ans, lengths[i]/2);
            if(i<(int)lengths.size()-1){
                ans = max(ans, min(lengths[i], lengths[i+1]));
            }
        }
        return ans;
    }
};
