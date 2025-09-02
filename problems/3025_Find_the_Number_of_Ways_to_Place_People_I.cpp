//
// Created by user on 2025/9/2.
//

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](vector<int> a, vector<int> b){
            return (a[0]==b[0])?(a[1]>b[1]):(a[0]<b[0]);
        });

        int ans = 0;

        for (int i = 0; i < points.size(); ++i) {
            int y1 = points[i][1];
            int bottom = INT_MIN;
            for (int j = i+1; j < points.size(); ++j) {
                int y2 = points[j][1];

                if(y2 <= y1 && y2 > bottom){
                    bottom = y2;
                    ans++;
                }
            }
        }
        return ans;
    }
};
