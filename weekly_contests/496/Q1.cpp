// Weekly Contest 496 - Q1
// Created automatically
// Created at 2026-04-05 17:31:25

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mirrorFrequency(string s) {
        vector<int> freq(36, 0);
        for (char ch : s) {
            if (isdigit(ch)) ++freq[ch - '0'];
            else ++freq[10 + ch - 'a'];
        }

        auto mirrorIndex = [](int idx) -> int {
            if (idx < 10) return 9 - idx;
            return 10 + (25 - (idx - 10));
        };

        int answer = 0;
        for (int idx = 0; idx < 36; ++idx) {
            int mirrored = mirrorIndex(idx);
            if (idx < mirrored) {
                answer += abs(freq[idx] - freq[mirrored]);
            }
        }

        return answer;
    }
};
