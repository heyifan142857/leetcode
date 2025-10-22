//
// Created by user on 2025/10/22.
//
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        if (n == 0) return 0;
        unordered_map<long long,int> freq;
        for (long long v : nums) freq[v]++;

        vector<pair<long long,int>> events;
        events.reserve(2*n);
        for (long long v : nums) {
            long long s = v - k;
            long long e = v + k;
            events.emplace_back(s, 1);
            events.emplace_back(e + 1, -1);
        }

        sort(events.begin(), events.end());

        set<long long> critical;
        for (auto &p : events) critical.insert(p.first);
        for (auto &kv : freq) critical.insert(kv.first);

        int ei = 0;
        long long curTotal = 0;
        int ans = 1;

        for (long long pos : critical) {
            while (ei < (int)events.size() && events[ei].first <= pos) {
                curTotal += events[ei].second;
                ei++;
            }

            int exact = 0;
            auto it = freq.find(pos);
            if (it != freq.end()) exact = it->second;

            ans = max(ans, (int)min<long long>(curTotal, (long long)exact + numOperations));

            ans = max(ans, (int)min<long long>(curTotal, (long long)numOperations));
        }
        return ans;
    }
};
