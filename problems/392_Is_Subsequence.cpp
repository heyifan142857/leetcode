//
// Created by azote on 1/19/26.
//
#include <string>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int flg1 = 0;
        int flg2 = 0;
        const int s_len = s.size();
        const int t_len = t.size();
        while (flg1 < s_len && flg2 < t_len) {
            if (s[flg1] == t[flg2]) {
                flg1++;
            }
            flg2++;
        }
        if (flg1 == s.size()) {
            return true;
        }
        return false;
    }
};
