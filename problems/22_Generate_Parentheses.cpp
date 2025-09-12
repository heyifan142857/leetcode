//
// Created by user on 2025/9/12.
//
#include <vector>
#include <string>
using namespace std;

class Solution {
    vector<string> ans;
    void _generateParenthesis(int l, int r, string& s){
        if(l == 0 && r == 0){
            ans.push_back(s);
            return;
        }
        if(l>0){
            s += '(';
            _generateParenthesis(l-1, r, s);
            s.pop_back();
        }
        if(l < r){
            s += ')';
            _generateParenthesis(l, r-1, s);
            s.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        string s;
        _generateParenthesis(n, n, s);
        return ans;
    }
};