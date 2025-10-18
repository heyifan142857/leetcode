//
// Created by user on 2025/10/18.
//
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> mp;
        mp['I'] = 1;
        mp['V'] = 5;
        mp['X'] = 10;
        mp['L'] = 50;
        mp['C'] = 100;
        mp['D'] = 500;
        mp['M'] = 1000;

        int res = 0;
        int prev = 0;

        int n = s.size();
        for (int i = n-1; i >= 0; --i) {
            int cur = mp[s[i]];
            if(cur >= prev){
                res += cur;
            }else{
                res -= cur;
            }
            prev = cur;
        }
        return res;
    }
};