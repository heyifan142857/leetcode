//
// Created by user on 2025/11/4.
//
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findXSum(vector<int> &nums, int k, int x) {
        int n = nums.size();
        vector<int> ans;

        for (int i = 0; i + k <= n; ++i) {
            unordered_map<int, int> freq;
            for (int j = i; j < i + k; ++j)
                freq[nums[j]]++;

            vector<pair<int, int>> items;
            for (auto &p: freq)
                items.push_back({p.first, p.second});

            sort(items.begin(), items.end(), [](auto &a, auto &b) {
                if (a.second != b.second)
                    return a.second > b.second;
                return a.first > b.first;
            });

            unordered_set<int> topx;
            for (int j = 0; j < (int) items.size() && j < x; ++j)
                topx.insert(items[j].first);

            long long sum = 0;
            for (int j = i; j < i + k; ++j)
                if (topx.count(nums[j]))
                    sum += nums[j];

            ans.push_back(sum);
        }

        return ans;
    }
};