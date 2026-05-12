// 1665. Minimum Initial Energy to Finish Tasks
// Created automatically
// Created at 2026-05-12 11:51:46

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] - a[0] > b[1] - b[0];
        });

        int ans = 0;
        int spent = 0;

        for (const auto& task : tasks) {
            ans = max(ans, spent + task[1]);
            spent += task[0];
        }

        return ans;
    }
};
