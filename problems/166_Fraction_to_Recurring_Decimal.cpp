//
// Created by user on 2025/9/24.
//
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if(numerator == 0){return "0";}

        string ans;

        if((numerator>0 && denominator<0) || (numerator<0&&denominator>0)){
            ans += '-';
        }

        long long num = numerator;
        long long denom = denominator;

        num = llabs(num);
        denom = llabs(denom);

        ans += to_string(num/denom);

        long long remain = num%denom;

        if(remain){
            ans += '.';
            unordered_map<long long, int> remainder;
            while (remain){
                if (remainder.contains(remain)){
                    ans.insert(remainder[remain], 1, '(');
                    ans += ')';
                    break;
                }
                remainder[remain] = ans.size();
                remain *= 10;
                long long cur = remain/denom;
                remain = remain % denom;
                ans += to_string(cur);
            }
        }

        return ans;
    }
};
