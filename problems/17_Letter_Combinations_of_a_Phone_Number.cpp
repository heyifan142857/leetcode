//
// Created by user on 2025/9/12.
//
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
    vector<string> ans;
    vector<vector<char>> list;
    void _letterCombinations(string& s, int flag){
        if(flag >= list.size()){
            if(s != ""){
                ans.push_back(s);
            }
            return;
        }
        for (auto c: list[flag]) {
            s += c;
            _letterCombinations(s, flag+1);
            s.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        unordered_map<char, vector<char>> mp;
        mp['2'] = {'a', 'b', 'c'};
        mp['3'] = {'d', 'e', 'f'};
        mp['4'] = {'g', 'h', 'i'};
        mp['5'] = {'j', 'k', 'l'};
        mp['6'] = {'m', 'n', 'o'};
        mp['7'] = {'p', 'q', 'r', 's'};
        mp['8'] = {'t', 'u', 'v'};
        mp['9'] = {'w', 'x', 'y', 'z'};

        for (auto d: digits) {
            list.push_back(mp[d]);
        }

        string s;
        _letterCombinations(s, 0);

        return ans;
    }
};