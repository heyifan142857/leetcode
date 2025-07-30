//
// Created by user on 2025/7/22.
//
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int max_sum = 0, current_sum = 0;
        unordered_set<int> seen;
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (seen.find(nums[right]) != seen.end()){
                seen.erase(nums[left]);
                current_sum -= nums[left];
                left++;
            }
            current_sum += nums[right];
            seen.insert(nums[right]);
            if (current_sum > max_sum){
                max_sum = current_sum;
            }
        }
        return max_sum;
    }
};

/*
官方题解

方法一：哈希表 + 前缀和
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> psum(n + 1);
        unordered_map<int, int> cnt;
        int ans = 0, pre = 0;
        for(int i = 0; i < n; ++i) {
            psum[i + 1] = psum[i] + nums[i];
            pre = max(pre, cnt[nums[i]]);
            ans = max(ans, psum[i + 1] - psum[pre]);
            cnt[nums[i]] = i + 1;
        }

        return ans;
    }
};

方法二：滑动窗口
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> seen;
        int ans = 0, psum = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            psum += nums[i];
            while (seen.count(nums[i])) {
                seen.erase(nums[j]);
                psum -= nums[j];
                j++;
            }
            seen.emplace(nums[i]);
            ans = max(ans, psum);
        }

        return ans;
    }
};
*/