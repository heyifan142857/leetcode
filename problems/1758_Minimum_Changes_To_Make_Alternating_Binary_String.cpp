// 1758. Minimum Changes To Make Alternating Binary String
// Created automatically
// Created at 2026-03-05 10:31:42

#include <string>
using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int count1 = 0, count2 = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] - '0' != i % 2) {
                count1++;
            }
            if (s[i] - '0' != (i + 1) % 2) {
                count2++;
            }
        }
        return min(count1, count2);        
    }
};