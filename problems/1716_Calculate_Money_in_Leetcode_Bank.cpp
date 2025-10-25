//
// Created by user on 2025/10/25.
//
class Solution {
public:
    int totalMoney(int n) {
        int a = n / 7;
        int b = n % 7;
        int part1 = (28 + 28 + (a - 1) * 7) * a / 2;
        int part2 = ((1 + a) + (1 + a + b - 1)) * b / 2;
        return part1 + part2;
    }
};