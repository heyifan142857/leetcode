//
// Created by user on 2025/8/26.
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, vector<int>> numbers;
        for (int i = 0; i < nums.size(); ++i) {
           numbers[nums[i]].push_back(i);
        }
        for (auto num: nums) {
            if(numbers.find(target-num) != numbers.end()){
                if(num != target-num){
                    vector<int> ans = {numbers[num][0], numbers[target-num][0]};
                    return ans;
                }else if(numbers[num].size()>1){
                    vector<int> ans = {numbers[num][0], numbers[num][1]};
                    return ans;
                }
            }
        }
        return {};
    }
};

/*
官方题解
 class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
 */