// 242. Valid Anagram
// Created automatically
// Created at 2026-03-12 11:44:15

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        
        unordered_map<char, int> charCount;
        
        for (char c : s) {
            charCount[c]++;
        }
        
        for (char c : t) {
            charCount[c]--;
        }
        
        for (const auto& pair : charCount) {
            if (pair.second != 0) return false;
        }
        
        return true;
    }
};