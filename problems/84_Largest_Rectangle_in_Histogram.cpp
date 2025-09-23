//
// Created by user on 2025/9/18.
//
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<pair<int, int>> s;
        vector<int> l(n, 0);
        vector<int> r(n, 0);

        for (int i = 0; i < n; ++i) {
            while (!s.empty() && s.top().first >= heights[i]){
                s.pop();
            }
            l[i] = s.empty()?-1:s.top().second;
            s.emplace(heights[i], i);
        }

        s = stack<pair<int, int>>();

        for (int i = n-1; i >= 0; --i) {
            while (!s.empty() && s.top().first >= heights[i]){
                s.pop();
            }
            r[i] = s.empty()?n:s.top().second;
            s.emplace(heights[i], i);
        }

        int maxArea = 0;
        for (int i = 0; i < n; ++i) {
            maxArea = max(maxArea, heights[i]*(r[i]-l[i]-1));
        }
        return maxArea;
    }
};