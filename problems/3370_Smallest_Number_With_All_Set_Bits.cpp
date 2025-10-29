//
// Created by user on 2025/10/29.
//
class Solution {
public:
    int smallestNumber(int n) {
        int digit = 1;
        while (digit < n) {
            if (!(digit & n)) {
                n += digit;
            }
            digit = digit << 1;
        }
        return n;
    }
};