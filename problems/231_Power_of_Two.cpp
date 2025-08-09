//
// Created by user on 2025/8/9.
//
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n <= 0){
            return false;
        }
        while (n > 1){
            int temp = n >> 1;
            if(n != (temp << 1)){
                return false;
            }
            n = temp;
        }
        return true;
    }
};