// 1784. Check if Binary String Has at Most One Segment of Ones
// Created automatically
// Created at 2026-03-06 09:58:18

#include <string>
using namespace std;
class Solution {
public:
    bool checkOnesSegment(string s) {
        int n = s.length();
        int i = 0;
        // Skip leading zeros
        while (i < n && s[i] == '0') {
            i++;
        }
        // Check if there's a segment of ones
        while (i < n && s[i] == '1') {
            i++;
        }
        // Skip trailing zeros
        while (i < n && s[i] == '0') {
            i++;
        }
        // If we've reached the end, it means there was at most one segment of ones
        return i == n;
    }
};