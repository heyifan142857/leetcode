//
// Created by user on 2025/9/15.
//
#include <vector>
using namespace std;

class Solution {
    int m;
    int n;
    bool _searchMatrix(vector<vector<int>>& matrix, int l, int r, int target){
        if(l>r){
            return false;
        }
        int mid = (l+r)/2;
        int x = mid / n;
        int y = mid % n;
        if(matrix[x][y] == target){
            return true;
        }else if(matrix[x][y] > target){
            return _searchMatrix(matrix, l, mid-1, target);
        }else{
            return _searchMatrix(matrix, mid+1, r, target);
        }
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = matrix[0].size();
        return _searchMatrix(matrix, 0, m*n-1, target);
    }
};