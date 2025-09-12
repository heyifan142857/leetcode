//
// Created by user on 2025/9/12.
//
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> ans;
    int t;
    void _combinationSum(const vector<int>& candidates, int p, int total, vector<int>& sub){
        if(total > t || p >= candidates.size()){
            return;
        }
        if(total == t){
            ans.push_back(sub);
            return;
        }
        sub.push_back(candidates[p]);
        _combinationSum(candidates, p, total+candidates[p], sub);
        sub.pop_back();
        _combinationSum(candidates, p+1, total, sub);
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        t = target;
        vector<int> sub;
        _combinationSum(candidates, 0, 0, sub);
        return ans;
    }
};