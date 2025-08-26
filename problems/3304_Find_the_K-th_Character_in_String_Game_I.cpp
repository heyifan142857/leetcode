//
// Created by user on 2025/7/29.
//
class Solution {
public:
    char kthCharacter(int k) {
        if(k == 1){
            return 'a';
        }
        int exponent = 0;
        int n = k;
        while(n > 1){
            exponent++;
            n = n >> 1;
        }
        int remaining = k - (1 << exponent);

        if(remaining == 0){
            return char('a' + exponent);
        }

        return char(kthCharacter(remaining)+1);
    }
};