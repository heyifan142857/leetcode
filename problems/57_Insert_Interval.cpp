// 57. Insert Interval
// Created automatically
// Created at 2026-03-13 15:27:33

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        for (const auto& interval : intervals) {
            if (interval[0] < newInterval[0] && interval[1] < newInterval[0]) {
                result.push_back(interval);
            } else if (interval[0] > newInterval[1]) {
                result.push_back(newInterval);
                newInterval = interval;
            } else {
                newInterval[0] = min(newInterval[0], interval[0]);
                newInterval[1] = max(newInterval[1], interval[1]);
            }
        }
        result.push_back(newInterval);
        return result;      
    }
};