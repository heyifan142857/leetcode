//
// Created by user on 2025/9/3.
//

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> mp;
        vector<long long> ps(n+1, 0);
        long long ans = LONG_LONG_MIN;
        for (int i = 0; i < n; ++i) {
            ps[i+1] = ps[i] + nums[i];
            if(mp.contains(nums[i]-k)){
                long long cur = ps[i+1] - ps[mp[nums[i]-k]];
                ans = max(ans, cur);
            }
            if(mp.contains(nums[i]+k)){
                long long cur = ps[i+1] - ps[mp[nums[i]+k]];
                ans = max(ans, cur);
            }
            if(mp.contains(nums[i])){
                if(ps[i] - ps[mp[nums[i]]]<0){
                    mp[nums[i]] = i;
                }
            }else{
                mp[nums[i]] = i;
            }
        }
        return ans==LONG_LONG_MIN?0:ans;
    }
};

int main(){
    Solution s;
    vector<int> nums = {-1,-2,-3,-4};
    s.maximumSubarraySum(nums, 2);
}