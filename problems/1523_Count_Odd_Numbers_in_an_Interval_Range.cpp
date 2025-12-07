//
// Created by azote on 12/7/25.
//
class Solution {
public:
    int countOdds(int low, int high) {
        if (low > high) {
            return 0;
        }
        int res = high - low + 1;
        if (low % 2) {
            res++;
        }
        if (high % 2) {
            res++;
        }
        res /= 2;
        return res;
    }
};
