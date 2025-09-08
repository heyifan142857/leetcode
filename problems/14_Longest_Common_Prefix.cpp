//
// Created by user on 2025/9/8.
//

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()){
            return "";
        }

        string ans = "";

        string s = strs[0];

        bool flag = false;

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            for (int j = 1; j < strs.size(); ++j) {
                if(i>=strs[j].size() || strs[j][i]!=c){
                    flag = true;
                    break;
                }
            }
            if(flag){
                break;
            }
            ans += c;
        }

        return ans;
    }
};