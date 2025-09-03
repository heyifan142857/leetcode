//
// Created by user on 2025/9/3.
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        int total = m * n;
        int cur = 0;
        int dir = 0;

        vector<int> ans;

        vector<vector<int>> mark = vector(m, vector(n, 0));
        pair<int, int> cur_pos = make_pair(0, 0);

        while (cur++ < total){
            mark[cur_pos.first][cur_pos.second] = 1;
            ans.push_back(matrix[cur_pos.first][cur_pos.second]);

            int nx = cur_pos.first+directions[dir].first;
            int ny = cur_pos.second+directions[dir].second;

            if(nx<0 || nx>=m || ny<0 || ny>=n || mark[nx][ny]==1){
                dir = (dir+1)%4;
                nx = cur_pos.first+directions[dir].first;
                ny = cur_pos.second+directions[dir].second;
            }
            cur_pos = make_pair(nx, ny);
        }

        return ans;
    }
};