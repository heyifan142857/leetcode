//
// Created by user on 2025/10/1.
//
#include <string>
using namespace std;

class Solution {
    string _longestPalindrome(const string s, int pos) {
        int l = pos, r = pos;
        while (l>=0 && r<s.size()){
            if(s[l] != s[r]){
                break;
            }
            l--;
            r++;
        }
        string ans = s.substr(l+1, r-l-1);

        if(pos+1<s.size() && s[pos]==s[pos+1]){
            l = pos;
            r = pos+1;
            while (l>=0 && r<s.size()){
                if(s[l] != s[r]){
                    break;
                }
                l--;
                r++;
            }
            string temp = s.substr(l+1, r-l-1);
            if(temp.size() > ans.size()){
                ans = temp;
            }
        }
        return ans;
    }
public:
    string longestPalindrome(string s) {
        string ans;
        for (int i = 0; i < s.size(); ++i) {
            string cur = _longestPalindrome(s, i);
            if(cur.size()>ans.size()){
                ans = cur;
            }
        }
        return ans;
    }
};