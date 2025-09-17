//
// Created by user on 2025/9/17.
//
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<pair<int, int>> s;
        vector<int> ans(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); ++i) {
            while (!s.empty()){
                if(s.top().first >= temperatures[i]){
                    break;
                }else{
                    auto top = s.top();
                    ans[top.second] = i - top.second;
                    s.pop();
                }
            }
            s.push({temperatures[i], i});
        }
        return ans;
    }
};