// 1541. Minimum Insertions to Balance a Parentheses String
// Created automatically
// Created at 2026-10-09 20:53:57

#include <string>
using namespace std;


class Solution {
public:
    int minInsertions(string s) {
        int left = 0;
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                left++;
            } else {
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } else {
                    ans++;
                }

                if (left > 0) {
                    left--;
                } else {
                    ans++;
                }
            }
        }

        return ans + left * 2;
    }
};