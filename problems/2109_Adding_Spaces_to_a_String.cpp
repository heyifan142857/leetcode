//
// Created by user on 2025/8/22.
//

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        string ans = "";
        auto it = spaces.begin();
        for (int i = 0; i < s.length(); ++i) {
            if(it != spaces.end() && *it == i){
                ans += ' ';
                it++;
            }

            ans += s[i];
        }
        return ans;
    }
};