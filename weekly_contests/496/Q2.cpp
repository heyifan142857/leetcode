// Weekly Contest 496 - Q2
// Created automatically
// Created at 2026-04-05 17:31:25

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findGoodIntegers(int n) {
        vector<int> answer;
        if (n < 2) return answer;

        int limit = 0;
        while (1LL * (limit + 1) * (limit + 1) * (limit + 1) <= n) ++limit;

        unordered_map<int, int> ways;
        vector<int> cubes(limit + 1, 0);
        for (int i = 1; i <= limit; ++i) {
            cubes[i] = i * i * i;
        }

        for (int a = 1; a <= limit; ++a) {
            for (int b = a; b <= limit; ++b) {
                long long sum = 1LL * cubes[a] + cubes[b];
                if (sum > n) break;
                ++ways[static_cast<int>(sum)];
            }
        }

        for (const auto& [sum, count] : ways) {
            if (count >= 2) answer.push_back(sum);
        }

        sort(answer.begin(), answer.end());
        return answer;
    }
};
