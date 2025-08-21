//
// Created by user on 2025/8/21.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> left(m, vector<int>(n, 0));

        int sum = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(mat[i][j] == 1){
                    if(j == 0){
                        left[i][j] = 1;
                    }else{
                        left[i][j] = left[i][j-1] + 1;
                    }
                }
                int cur = left[i][j];
                for (int k = i; k >= 0; --k) {
                    cur = min(cur, left[k][j]);
                    if(cur == 0){
                        break;
                    }
                    sum += cur;
                }
            }
        }
        return sum;
    }
};