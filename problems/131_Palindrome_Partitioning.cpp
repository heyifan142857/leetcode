//
// Created by user on 2025/9/12.
//
#include <string>
#include <vector>
using namespace std;

class Solution {
    vector<vector<string>> ans;
    bool isPalindrome(string s){
        int l = 0;
        int r = s.size()-1;
        while (l < r){
            if(s[l] != s[r]){
                return false;
            }
            l++;
            r--;
        }
        return true;
    }
    void _partition(string s, int start, int length, vector<string>& sub, int total){
        if(start+length > s.size()){
            if(total == s.size()){
                ans.push_back(sub);
            }
            return;
        }
        string cur = s.substr(start, length);
        if(isPalindrome(cur)){
            sub.push_back(cur);
            _partition(s, start+length, 1, sub, total+cur.size());
            sub.pop_back();
        }
        _partition(s, start, length+1, sub, total);
    }
public:
    vector<vector<string>> partition(string s) {
        vector<string> sub;
        _partition(s, 0, 1, sub, 0);
        return ans;
    }
};