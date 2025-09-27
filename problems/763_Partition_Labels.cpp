//
// Created by user on 2025/9/25.
//
#include <string>
#include <vector>
#include <climits>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> start(26, INT_MAX);
        vector<int> end(26, INT_MIN);
        unordered_set<int> include;

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            int cur = c - 'a';
            if(!include.contains(cur)){
                include.insert(cur);
            }
            if(start[cur]>i){
                start[cur] = i;
            }
            if(end[cur]<i){
                end[cur] = i;
            }
        }

        vector<pair<int, int>> list;

        for (auto c: include) {
            list.push_back({start[c], end[c]});
        }

        sort(list.begin(), list.end());

        vector<pair<int, int>> merge_list;

        for (auto e: list) {
            if(merge_list.empty() || merge_list.back().second<e.first){
                merge_list.push_back(e);
            }else{
                int temp1 = merge_list.back().first;
                int temp2 = merge_list.back().second;
                merge_list.pop_back();
                merge_list.push_back({temp1, max(temp2, e.second)});
            }
        }

        vector<int> res;
        for (auto e: merge_list) {
            res.push_back(e.second-e.first+1);
        }

        return res;
    }
};