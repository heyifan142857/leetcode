// 1910. Remove All Occurrences of a Substring
// Created automatically
// Created at 2026-03-21 20:28:01

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeOccurrences(string s, string part) {
        string result;
        size_t partLength = part.size();

        for (char ch : s) {
            result.push_back(ch);
            if (result.size() >= partLength &&
                result.compare(result.size() - partLength, partLength, part) == 0) {
                result.resize(result.size() - partLength);
            }
        }

        return result;
    }
};
