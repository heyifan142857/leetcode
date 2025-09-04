//
// Created by user on 2025/9/4.
//

#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if(matrix[i][j] == target){
                    return true;
                }
                if(matrix[i][j] > target){
                    break;
                }
            }
        }
        return false;
    }
};