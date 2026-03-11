// 1009. Complement of Base 10 Integer
// Created automatically
// Created at 2026-03-11 09:36:14
class Solution {
public:
    int bitwiseComplement(int n) {
        if (n == 0) return 1;
        int mask = 1;
        while (mask < n) {
            mask = (mask << 1) | 1;
        }
        return n ^ mask;
    }
};