// 3121. Count the Number of Special Characters II
// Created automatically
// Created at 2026-05-27 09:11:36

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        int count = 0;
        vector<int> freq(26, 0);
        for (char c : word) {
            int index = c - 'a';
            if (index >= 0 && index < 26) {
                if (freq[index] == 0) {
                    freq[index]++;
                } else if (freq[index] == 2) {
                    count--;
                    freq[index] = -1;
                }
            } else {
                index += 32;
                if (freq[index] == 0) {
                    freq[index] = -1;
                } else if (freq[index] == 1) {
                    count++;
                    freq[index]++;
                }
            }
        }
        return count;
    }
}; 