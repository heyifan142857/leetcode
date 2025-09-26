//
// Created by user on 2025/9/26.
//
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int cnt = 0;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 2; i < n; ++i) {
            int l = 0;
            int r = i-1;
            while (l <= r){
                if(nums[l] + nums[r] > nums[i]){
                    cnt += r-l;
                    r--;
                }else{
                    l++;
                }
            }
        }
        return cnt;
    }
};