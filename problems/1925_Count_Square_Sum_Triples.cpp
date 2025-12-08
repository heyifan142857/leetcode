//
// Created by azote on 12/8/25.
//
#include <cmath>

class Solution {
    bool isPerfectSquare(int n) {
        if (n < 0) return false;
        int root = static_cast<int>(std::sqrt(n));
        return root * root == n;
    }

public:
    int countTriples(int n) {
        int res = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (i * i + j * j > n * n) {
                    continue;
                }
                if (isPerfectSquare(i * i + j * j)) {
                    res += 2;
                }
            }
        }
        return res;
    }
};
