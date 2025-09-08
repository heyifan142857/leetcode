//
// Created by user on 2025/9/8.
//

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        int a = 0;
        int b = 0;
        int digit = 1;
        while (n>0){
            int cur = n%10;

            if(cur <= 1 && n>=10){
               a += 5 * digit;
               b += (5+cur) * digit;
               n -= 10;
            }else if(cur <= 1 && n>=10){
                b += (cur) * digit;
            }else{
                a += (cur/2) * digit;
                b += ((cur+1)/2) * digit;
            }

            n = n/10;
            digit *= 10;
        }
        return {a, b};
    }
};