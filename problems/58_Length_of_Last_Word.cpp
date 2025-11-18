//
// Created by azote on 11/18/25.
//
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int len = s.size();

        bool start = false;
        int res = 0;

        for (int i = len - 1; i >= 0; --i) {
            if (s[i] != ' ') {
                start = true;
            }

            if (start) {
                if (s[i] == ' ') {
                    break;
                }
                res++;
            }
        }

        return res;
    }
};
