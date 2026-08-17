// 3302. Find the Lexicographically Smallest Valid Sequence
// Created automatically
// Created at 2026-08-08 21:37:09

#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        if (n < m)
            return {};

        vector<int> right(m, -1);

        int j = m - 1;
        for (int i = n - 1; i >= 0 && j >= 0; --i) {
            if (word1[i] == word2[j]) {
                right[j] = i;
                --j;
            }
        }

        vector<int> answer;
        bool changed = false;
        j = 0;

        for (int i = 0; i < n && j < m; ++i) {
            if (word1[i] == word2[j]) {
                answer.push_back(i);
                ++j;
            } else if (!changed && (j == m - 1 ||
                                    (right[j + 1] != -1 && i < right[j + 1]))) {
                answer.push_back(i);
                ++j;
                changed = true;
            }
        }

        return j == m ? answer : vector<int>{};
    }
};
