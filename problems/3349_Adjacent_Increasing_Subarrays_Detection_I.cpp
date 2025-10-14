//
// Created by user on 2025/10/14.
//
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
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

        for (int i = 0; i < (int)lengths.size(); ++i) {
            if(lengths[i]>=2*k){
                return true;
            }
            if(i<(int)lengths.size()-1&&(lengths[i]>=k&&lengths[i+1]>=k)){
                return true;
            }
        }
        return false;
    }
};