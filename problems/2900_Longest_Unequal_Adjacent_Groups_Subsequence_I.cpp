//
// Created by user on 2025/7/30.
//

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
        int n = words.size();
        int flag = -1;
        vector<string> ans;
        for (int i = 0; i < n; ++i) {
            if(flag != groups[i]){
                flag = groups[i];
                ans.push_back(words[i]);
            }
        }
        return ans;
    }
};