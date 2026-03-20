// 2183. Count Array Pairs Divisible by K
// Created automatically
// Created at 2026-03-20 15:02:47

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        long long answer = 0;
        unordered_map<int, int> count_by_gcd;

        for (int num : nums) {
            int current_gcd = gcd(num, k);

            for (const auto& [previous_gcd, frequency] : count_by_gcd) {
                if (1LL * previous_gcd * current_gcd % k == 0) {
                    answer += frequency;
                }
            }

            ++count_by_gcd[current_gcd];
        }

        return answer;
    }
};
