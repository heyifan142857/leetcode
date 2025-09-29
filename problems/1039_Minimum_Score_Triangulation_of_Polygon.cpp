//
// Created by user on 2025/9/29.
//
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
    unordered_map<int, int> memo;
    int dp(vector<int>& values, int l, int r){
        if(l+2>r){
            return 0;
        }
        if(l+2==r){
            return values[l] * values[l+1] * values[l+2];
        }
        int key = l*values.size()+r;
        if(!memo.contains(key)){
            int minVal = INT_MAX;
            for (int i = l+1; i < r; ++i) {
                minVal = min(minVal, values[l]*values[r]*values[i]+dp(values, l, i)+ dp(values, i, r));
            }
            memo[key] = minVal;
        }
        return memo[key];
    }
public:
    int minScoreTriangulation(vector<int>& values) {
        return dp(values, 0, values.size()-1);
    }
};