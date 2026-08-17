// 3090. Maximum Length Substring With Two Occurrences
// Created automatically
// Created at 2026-08-14 23:19:34

#include <algorithm>
#include <array>
#include <string>
using namespace std;

class Solution {
public:
    int maximumLengthSubstring(string s) {
        array<int, 26> count{};
        int answer = 0;

        for (int left = 0, right = 0; right < static_cast<int>(s.size());
             ++right) {
            ++count[s[right] - 'a'];

            while (count[s[right] - 'a'] > 2) {
                --count[s[left] - 'a'];
                ++left;
            }

            answer = max(answer, right - left + 1);
        }

        return answer;
    }
};
