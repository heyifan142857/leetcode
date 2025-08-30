//
// Created by user on 2025/8/30.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            return a[0]<b[0];
        });
        int cur = 1;
        int start = intervals[0][0];
        int end = intervals[0][1];
        vector<vector<int>> ans;
        while (cur < intervals.size()){
            if(intervals[cur][0] <= end){
                end = max(end, intervals[cur][1]);
            }else{
                ans.push_back({start, end});
                start = intervals[cur][0];
                end = intervals[cur][1];
            }
            cur++;
        }
        ans.push_back({start, end});
        return ans;
    }
};