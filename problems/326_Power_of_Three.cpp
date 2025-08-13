//
// Created by user on 2025/8/13.
//
class Solution {
public:
    bool isPowerOfThree(int n) {
        int d = n;
        if(d <= 0){
            return false;
        }
        while (d > 1){
            if(d % 3){
                return false;
            }
            d /= 3;
        }
        return true;
    }
};