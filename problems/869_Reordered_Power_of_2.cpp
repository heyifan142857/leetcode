//
// Created by user on 2025/8/10.
//

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    bool isPowerOfTwo(int n) {
        if (n <= 0){
            return false;
        }
        if (n == 1){
            return true;
        }
        if ((n & 1) == 1){
            return false;
        }
        for (int i = n; i > 1; i >>=1){
            if ((i & 1) == 1){
                return false;
            }
        }
        return true;
    }
public:
    bool reorderedPowerOf2(int n) {
        vector<int> digits;
        int t = n;
        while(t > 0){
            digits.push_back(t % 10);
            t /= 10;
        }
        int digit_count = digits.size();
        sort(digits.begin(), digits.end());

        do {
            if(digits[0] == 0){
                continue;
            }
            int cur = 0;
            for (int i = 0; i < digit_count; ++i) {
                int part = digits[i];
                for (int k = 0; k < digit_count - 1 - i; ++k) {
                    part *= 10;
                }
                cur += part;
            }
            if(isPowerOfTwo(cur)){
                return true;
            }
        } while (next_permutation(digits.begin(), digits.end()));

        return false;
    }
};