//
// Created by user on 2025/9/27.
//
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
    double handleArea(int x1, int y1, int x2, int y2, int x3, int y3){
        return 1.0*abs(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2))/2;
    }
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int n = points.size();
        double ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                for (int k = j+1; k < n; ++k) {
                    ans = max(ans, handleArea(points[i][0], points[i][1], points[j][0], points[j][1], points[k][0], points[k][1]));
                }
            }
        }
        return ans;
    }
};