//
// Created by azote on 11/26/25.
//
#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int hay_size = haystack.size();
        int need_size = needle.size();
        char start = needle[0];
        for (int i = 0; i < hay_size - need_size + 1; ++i) {
            if (haystack[i] == start) {
                bool has_diff = false;
                for (int j = 0; j < need_size; ++j) {
                    if (haystack[i + j] != needle[j]) {
                        has_diff = true;
                        break;
                    }
                }
                if (!has_diff) {
                    return i;
                }
            }
        }
        return -1;
    }
};
