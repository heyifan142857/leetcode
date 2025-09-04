//
// Created by user on 2025/9/3.
//

#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        double center = 1.0 * (n-1) / 2;

        for (int i = 0; i < (n+1)/2; ++i) {
            for (int j = i; j < n-1-i; ++j) {
                int x = i;
                int y = j;
                int first = matrix[i][j];
                for (int k = 0; k < 3; ++k) {
                    int nx = (int)(2 * center - y);
                    int ny = (int)(x);
                    matrix[x][y] = matrix[nx][ny];
                    x = nx;
                    y = ny;
                }
                matrix[x][y] = first;
            }
        }
    }
};