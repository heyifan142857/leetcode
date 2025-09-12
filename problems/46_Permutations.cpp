//
// Created by user on 2025/9/12.
//

#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> ans;
    void _permute(const vector<int>& nums, vector<int>& path){
        for (auto num: nums) {
            bool exist = false;
            for (auto n: path) {
                if(num == n){
                    exist = true;
                    break;
                }
            }
            if(exist){
                continue;
            }else{
                path.push_back(num);
                if(nums.size() == path.size()){
                    ans.push_back(path);
                }
                _permute(nums, path);
            }
            path.pop_back();
        }
    };
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> path;
        _permute(nums, path);

        return ans;
    }
};