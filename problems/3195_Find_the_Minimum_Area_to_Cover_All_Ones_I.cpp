//
// Created by user on 2025/8/22.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> count(m, vector<int>(n, 0));

        pair<int, int> p2(0, 0);

        int a = 0;
        int b = 0;

        int total = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int cur = 0;
                if(i==0 && j==0){
                    cur = 0;
                }else if(i==0){
                    cur = count[i][j-1];
                }else if(j==0){
                    cur = count[i-1][j];
                }else{
                    cur = count[i-1][j] + count[i][j-1] - count[i-1][j-1];
                }
                if(grid[i][j] == 1){
                    cur++;
                }
                if(cur > total){
                    total = cur;
                    p2 = make_pair(i, j);
                }
                count[i][j] = cur;
            }
        }
        for (int i = 0; i < m; ++i) {
            if(count[i][n-1] != 0){
                a = i;
                break;
            }
        }

        for (int i = 0; i < n; ++i) {
            if(count[m-1][i] != 0){
                b = i;
                break;
            }
        }

        return (p2.first-a+1)*(p2.second-b+1);
    }
};