//
// Created by user on 2025/7/25.
//
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using timePos = pair<int, pair<int, int>>;

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();

        vector<vector<int>> timeMap(n, vector<int>(m, INT_MAX));

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        timeMap[0][0] = 0;

        priority_queue<timePos> timePosList;

        timePosList.push({0, {0, 0}});

        while(!timePosList.empty()){
            timePos curTimePos = timePosList.top();
            timePosList.pop();

            for (pair<int, int> direction: directions) {
                int i = curTimePos.second.first;
                int j = curTimePos.second.second;
                int nn = i + direction.first;
                int nm = j + direction.second;

                if(nn >= 0 && nn < n && nm >= 0 && nm < m){
                    int new_dist = max(moveTime[nn][nm], timeMap[i][j])+1;
                    if(new_dist < timeMap[nn][nm]){
                        timeMap[nn][nm] = new_dist;
                        timePosList.push({new_dist, {nn, nm}});
                    }
                }
            }
        }
        return timeMap[n-1][m-1];
    }
};