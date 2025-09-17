//
// Created by user on 2025/9/17.
//
#include <string>
#include <unordered_set>
#include <stack>
#include <vector>
using namespace std;

class Solution {
    unordered_set<int> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    vector<string> nums;
    vector<string> strs;
public:
    string decodeString(string s) {
        nums.emplace_back("");
        strs.emplace_back("");

        bool handleNum = false;

        for (auto c: s) {
            if(c == '['){
                handleNum = false;
                continue;
            }
            if(c == ']'){
                handleNum = false;
                int cnt = stoi(nums[nums.size()-1]);
                for (int i = 0; i < cnt; ++i) {
                    strs[nums.size()-2] += strs[nums.size()-1];
                }
                nums.pop_back();
                strs.pop_back();
                continue;
            }

            if(digits.contains(c)){
                if(!handleNum){
                    handleNum = true;
                    nums.emplace_back("");
                    strs.emplace_back("");
                }
                nums[nums.size()-1] += c;
            }else{
                handleNum = false;
                strs[strs.size()-1] += c;
            }
        }
        return strs[0];
    }
};