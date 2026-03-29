// Weekly Contest 495 - Q1
// Created automatically
// Created at 2026-03-29 14:08:38

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstMatchingIndex(string s) {
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] == s[n - i - 1]) {
                return i;
            }
        }
        return -1;
    }
};
