//
// Created by azote on 12/7/25.
//
#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0;
        int r = s.size() - 1;

        while (l < r) {
            if (!isalnum(s[l])) {
                l++;
                continue;
            }
            if (!isalnum(s[r])) {
                r--;
                continue;
            }

            const char left = tolower(s[l]);
            const char right = tolower(s[r]);

            if (left != right) {
                return false;
            }

            l++;
            r--;
        }
        return true;
    }
};
